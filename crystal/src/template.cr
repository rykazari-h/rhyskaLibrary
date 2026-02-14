require "header.cr"
require "ioset.cr"
macro ios;IOset;end
at_exit { ios.flush }
