require "header.cr"
require "fastio.cr"
fr, fw = Fastread.new, Fastwrite.new
at_exit { fw.flush }
