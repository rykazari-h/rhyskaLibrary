require "header.cr"
require "ioset.cr"
ios = IOset.new
at_exit { ios.flush }
