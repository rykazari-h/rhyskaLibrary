require "header.cr"
require "ioset.cr"
ios = Ioset.new
at_exit { ios.flush }
