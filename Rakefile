Basedir = '.'

require "#{Basedir}/scripts/rakefuns.rb"
require "#{Basedir}/scripts/rakeconsts.rb"

Incldir = "#{Basedir}/include/starlia"
Builddir = "#{Basedir}/build"

Compilers[:cpp][1] << "I #{Incldir}"

Final = "#{Builddir}/libstarlia.a"

task :default do
	sh "cd src/core && rake"
	sh "cd src/testbench && rake"
end

task :clean do
	sh "cd src/core && rake clean"
	sh "cd src/testbench && rake clean"
end

task :distclean do
	sh "cd src/core && rake distclean"
	sh "cd src/testbench && rake distclean"
end

task :install do
	sh "su -c 'cp include/starlia /usr/local/include -r && cp #{Final} /usr/local/lib'"
end

task :uninstall do
	sh "su -c 'rm /usr/local/include/starlia -r && rm /usr/local/lib/libstarlia.a'"
end
