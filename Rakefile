require '../scripts/rakefuns.rb'
require '../scripts/rakeconsts.rb'

Libdir = '/usr/local/lib'
Incldir = '/usr/local/include/starlia'

Final = 'libstarlia.a'

task :default => Final

file Depend do
	makedep Src, Depend
end

import Depend

concfile Final => Obj do
	invoke Compilers[:ar], Obj, Final, ''
end

task :clean do
	sh "#{Rm} #{Obj}"
	sh "#{Rm} #{Depend}"
end

task :distclean => :clean do
	sh "#{Rm} #{Final}"
end

task :install => Final do
	sh "su -c 'mkdir -p #{Incldir} && cp #{Final} #{Libdir} && cp #{Head} #{Incldir} && cp #{Inl} #{Incldir}'"
end

task :uninstall do
	str = "#{Libdir}#{Final} "
	Head.each { |h| str += "#{Incldir}/#{h} " }
	Inl.each { |i| str += "#{Incldir}/#{i} " }

	sh "su -c '#{Rm} #{str} && rmdir #{Incldir}'"
end
