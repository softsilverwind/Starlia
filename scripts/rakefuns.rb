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

require 'rake'

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

def invoke compiler, source, output, outputflag = '-o'
	it = "#{compiler[0]} "
	compiler[1].each { |flag| it += "-#{flag} " }
	it += "#{outputflag} #{output} #{source} "
	compiler[2].each { |flag| it += "-#{flag} " }

	sh it  # lol
end

def gencppdeps filename
	compiler = Compilers[:cpp]
	it = "#{compiler[0]} "
	compiler[1].each { |flag| it += "-#{flag} " }
	it += "#{filename} "
	compiler[2].each { |flag| it += "-#{flag} " }
	it += '-M'
	x = File.popen "#{it}"
	x = x.read.gsub!(/\\/) {}.split(' ')
	x.shift
	return x;
#	File.read(filename).scan(/#include "([^"]*)"/).map { |i| i[0] }
end

def objify filename
	filename.gsub(/\.[^.]*$/, ".o")
end

def makedep sources, dependfile
	dep = File.open dependfile, 'w'
	sources.each do |x|
		dep.puts "rule '#{objify x}' => #{(gencppdeps x) << x} do"
		dep.puts "\tinvoke Compilers[:cpp], '#{x}', '#{objify x}'"
		dep.puts "end"
		dep.puts
	end
	dep.close
end
