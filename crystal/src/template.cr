require "header.cr"
require "ioset.cr"
IOSETi = IOset.new
@[AlwaysInline]; def ios; IOSETi; end
at_exit { ios.flush }
