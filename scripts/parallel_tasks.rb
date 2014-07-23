require 'rake'

module Parallel
	CORES = `cat /proc/cpuinfo | grep processor | wc -l`.to_i

	def self.min x, y
		(x < y) ? x : y
	end

	def self.for arr, threads = CORES
		arr = arr.to_a
		len = arr.length
		thrarr = []

		threads.times do |t|
			thrarr << Thread.new do
				start = t * len / threads
				fin = min((t+1) * len / threads - 1, len-1)

				start.upto fin do |elem|
					yield arr[elem]
				end
			end
		end

		thrarr.each { |thr| thr.join }
		nil
	end
end

module Rake
	class ConcurrentFileTask < FileTask
		private
		def invoke_prerequisites(args, invocation_chain)
			Parallel.for(@prerequisites) do |r|
				application[r, @scope].invoke_with_call_chain(args, invocation_chain)
			end
		end
	end

	class ConcurrentTask < Task
		private
		def execute(args=nil)
			args ||= EMPTY_TASK_ARGS
			if application.options.dryrun
				$stderr.puts "** Execute (dry run) #{name}"
				return
			end
			if application.options.trace
				$stderr.puts "** Execute #{name}"
			end
			application.enhance_with_matching_rule(name) if @actions.empty?
			Parallel.for(@actions) do |act|
				case act.arity
				when 1
					act.call(self)
				else
					act.call(self, args)
				end
			end
		end

		def invoke_prerequisites(task_args, invocation_chain)
			Parallel.for(prerequisite_tasks) do |prereq|
				puts "#{prereq}.inspect"
				prereq_args = task_args.new_scope(prereq.arg_names)
				prereq.invoke_with_call_chain(prereq_args, invocation_chain)
			end
		end
	end
end

def concfile *args, &block
	Rake::ConcurrentFileTask.define_task(*args, &block)
end

def concrule *args, &block
	Rake::ConcurrentTask.create_rule(*args, &block)
end
