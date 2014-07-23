require 'pathname'

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
	it += '-MM -MG'
	File.popen "#{it}" do |fp|
		x = fp.read.gsub!(/\\/, "")
		if x.nil?
			return []
		else
			x = x.split(' ')
			x.shift
			return x
		end
	end
#	File.read(filename).scan(/#include "([^"]*)"/).map { |i| i[0] }
end

def rem_ext filename
	filename.gsub(/\.[^.]*$/, "")
end

def makedep sources, mbys, dependfile
	File.open dependfile, 'w' do |dep|
		sources.each do |x|
			dep.puts %{rule '#{rem_ext(x) + ".o"}' => #{(gencppdeps x) << x} do}
			dep.puts %{\tinvoke Compilers[:cpp], '#{x}', '#{rem_ext(x) + ".o"}'}
			dep.puts %{end}
			dep.puts
		end

		mbys.each do |x|
			dep.puts %{rule %r{#{rem_ext(x)}\.(?:cpp|h)} do}
			dep.puts %{\tembassy "#{x}"}
			dep.puts %{end}
			dep.puts
			dep.puts %{rule '#{rem_ext(x)}.o' => ['#{rem_ext(x)}.cpp'] do}
			dep.puts %{\tinvoke Compilers[:cpp], '#{rem_ext(x) + ".cpp"}', '#{rem_ext(x) + ".o"}'}
			dep.puts %{end}
			dep.puts
		end
	end
end

def make_valid_id id
	id.gsub(/\./, "_").gsub(/\//, "_").gsub(/[^a-zA-Z_0-9]/, "").gsub(/^[0-9]*/, "")
end

class Fixnum
	def to_hex pad
		ret = to_s(16)
		return "0" * (pad - ret.size) + ret
	end
end

def embassy mby
	puts "Parsing #{mby}"

	assethash = {}

	File.read(mby).split("\n").each do |assetfile|
		unless assetfile.empty?
			if Pathname.new(assetfile).relative?
				assetfile = (Pathname.new(mby).dirname + assetfile).to_s
			end

			str = ""

			asset = File.read(assetfile)
			asset.each_byte do |b|
				str << "\\x#{b.to_hex(2)}"
			end

			assethash[assetfile] = str
		end
	end

	cppname = rem_ext(mby) + ".cpp"
	hname = rem_ext(mby) + ".h"
	hnameUP = make_valid_id(hname.upcase)

	File.open(cppname, "w") do |fp|
		for key, val in assethash do
			fp.puts %{const char *#{make_valid_id key} = "#{val}";\n}
		end
	end

	File.open(hname, "w") do |fp|
		fp.puts %{#ifndef __#{hnameUP}__\n#define __#{hnameUP}__\n}
		fp.puts
		for key, val in assethash do
			fp.puts %{extern const char *#{make_valid_id key};\n}
		end
		fp.puts
		fp.puts %{#endif}
	end
end
