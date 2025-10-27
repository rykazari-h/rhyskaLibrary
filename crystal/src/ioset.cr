class IOset
	BUFS = 1 << 17
	def initialize;@buf = Bytes.new BUFS;@size = 0;@idx = 0;@obuf = Bytes.new BUFS;@oidx = 0;@stk = StaticArray(UInt8, 20).new(0);@precision = 8;end
	def fill;@size = STDIN.read @buf;@idx = 0;end
	def read_byte : UInt8?;fill if @idx >= @size;return nil if @size == 0;b = @buf[@idx];@idx += 1;b;end
	def trim;loop do;fill if @idx >= @size;return if @size == 0;b = @buf[@idx];if b<=32;@idx += 1;else return;end;end;end
	def read_line : String;c = read_byte;return "" if !c;s = String.build do |i|;while c && c != 10;i.write_byte c;c = read_byte;end;end;s;end
	def gets : String;c = read_byte;return "" if !c;while c && c <= 32;c = read_byte;return "" if !c;end;s = String.build do |i|;while c && c > 32;i.write_byte c;c = read_byte;end;end;s;end
	macro geti_g(name, type)
		def {{name}} : {{type}}
			c = read_byte
			while c && c <= 32
				c = read_byte
			end
			sign = 1
			if c == 45
				sign = -1
				c = read_byte
			end
			n : {{type}} = 0
			while c && c >= 48 && c <= 57
				n = n * 10 + (c ^ 48)
				c = read_byte
			end
			n * sign
		end
	end
	geti_g(geti, Int32);geti_g(geti64, Int64)
	# ---output---
	def write_byte(b : UInt8);flush if @oidx == BUFS;@obuf[@oidx] = b;@oidx += 1;end
	def write(s : String);s.each_byte { |b| write_byte b };end
	def write_int(x : Int);i = 0;n = x < 0 ? -x : x;loop do;@stk[i] = (n % 10).to_u8;i += 1;break if (n //= 10) <= 0;end;write_byte 45 if x < 0;while i > 0;write_byte @stk[i-=1] | 48;end;end
	def setprecision(x);@precision = x;end
	def write_float(x : Float);v = x.to_i64;f = ((x - v).abs * 10i64 ** @precision).round.to_i64;write_int v;write_byte 46;i = 0;loop do;@stk[i] = (f % 10).to_u8;i += 1;break if (f //= 10) <= 0;end;(@precision - i).times { write_byte 48};while i > 0;write_byte @stk[i-=1] | 48;end;end
	def flush;return if @oidx == 0;STDOUT.write @obuf[0, @oidx];@oidx = 0;end
	def putv(x : Array(Array(T))) forall T
		return if x.empty?
		putv x[0]
		(1...x.size).each { |i| write_byte 10;putv x[i] }
	end
	def putv(x)
		case x
		when Int then write_int x
		when Char then write_byte x.ord.to_u8
		when Float then write_float x
		when String then write x
		when Bool then write_byte x ? 49u8 : 48u8
		else
			return if x.empty?
			putv x[0]
			(1...x.size).each { |i| write_byte 32;putv x[i] }
		end
	end
	def outl;write_byte 10;end
	def outl(*x, sep = " ", endl = "\n")
		putv x[0]
		(1...x.size).each { |i|write sep;putv x[i]}
		write endl
	end
end
