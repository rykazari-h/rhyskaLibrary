require "big"
lib LibIOset
  fun memcpy(dest : Void*, src : Void*, n : UInt64) : Void*
  fun read(fd : Int32, buf : Void*, count : UInt64) : Int64
  fun write(fd : Int32, buf : Void*, count : UInt64) : Int64
  fun fcntl(fd : Int32, cmd : Int32, ...) : Int32
  F_GETFL = 3
  F_SETFL = 4
  O_NONBLOCK = 0o4000
end
class IOset
  BUFS = 1 << 20
  OT = Pointer(UInt32).malloc(10000)
  POW10 = {1i64, 10i64, 100i64, 1000i64, 10000i64, 100000i64, 1000000i64, 10000000i64, 100000000i64, 1000000000i64, 10000000000i64, 100000000000i64, 1000000000000i64, 10000000000000i64, 100000000000000i64 , 1000000000000000i64, 10000000000000000i64}
  REV = StaticArray(UInt32, 10).new(0u32)
  @buf = Pointer(UInt8).malloc BUFS; @obuf = Pointer(UInt8).malloc BUFS; @precision = 10
  @ptr : UInt8*; @end : UInt8*; @optr : UInt8*; @oend : UInt8*
  @in_io : IO = STDIN; @out_io : IO = STDOUT; @in_fd = 0; @out_fd = 1
  def initialize
    10u32.times { |a| 10.times { |b| 10.times { |c| 10.times { |d| OT[a * 1000 + b * 100 + c * 10 + d] = a + 48 | b + 48 << 8 | c + 48 << 16 | d + 48 << 24 } } } }
    force_blocking(0)
    force_blocking(1)
    @ptr = @buf
    @end = @buf
    @optr = @obuf
    @oend = @obuf + BUFS
  end
  def set_io(input : IO = STDIN, output : IO = STDOUT) : Nil
    @in_io = input; @out_io = output
    @in_fd = input.is_a?(IO::FileDescriptor) ? input.fd : -1
    @out_fd = output.is_a?(IO::FileDescriptor) ? output.fd : -1
    force_blocking(@in_fd)
    force_blocking(@out_fd)
  end
  private def force_blocking(fd : Int32) : Nil
    return if fd < 0
    flags = LibIOset.fcntl(fd, LibIOset::F_GETFL)
    if flags >= 0
      LibIOset.fcntl(fd, LibIOset::F_SETFL, flags & ~LibIOset::O_NONBLOCK)
    end
  end
  def fill : Nil
    if @in_fd < 0
      res = @in_io.read Slice.new @buf, BUFS
      @end = @buf + res
    else
      res = LibIOset.read(@in_fd, @buf.as(Void*), BUFS)
      @end = @buf + (res < 0 ? 0 : res.to_i)
    end
    @ptr = @buf
  end
  def eof? : Bool
    fill if @end <= @ptr; @ptr == @end
  end
  def read_byte : UInt8?
    fill if @end <= @ptr; return nil if @ptr == @end; b = @ptr.value; @ptr += 1; b
  end
  def trim : Nil
    iptr = @ptr
    loop do
      (fill; iptr = @ptr) if @end <= iptr
      break if iptr == @end || 32 < iptr.value
      iptr += 1
    end
    @ptr = iptr
  end
  def getc : Char
    fill if @end <= @ptr
    c = nil.as(UInt8?)
    iptr = @ptr
    if iptr == @end
      c = nil
    else
      c = iptr.value; iptr += 1
    end
    while c && c <= 32
      (fill; iptr = @ptr) if @end <= iptr
      if iptr == @end
        c = nil
      else
        c = iptr.value; iptr += 1
      end
    end
    raise "End of file reached (IOset.getc)" if !c
    @ptr = iptr
    c.not_nil!.chr
  end
  def read_line : String
    raise "End of file reached (IOset.read_line)" if @end <= @ptr && (fill; @end <= @ptr)
    iptr = @ptr
    start = iptr
    while iptr < @end && iptr.value != 10
      iptr += 1
    end
    if iptr < @end
      len = iptr - start
      @ptr = iptr + 1
      return String.new(start, len)
    end
    @ptr = iptr
    String.build do |io|
      io.write Slice.new(start, (@end - start).to_i)
      while (b = read_byte) && b != 10
        io.write_byte b
      end
    end
  end
  def gets : String
    trim
    raise "End of file reached (IOset.gets)" if @end <= @ptr && (fill; @end <= @ptr)
    iptr = @ptr
    start = iptr
    while iptr < @end && iptr.value > 32
      iptr += 1
    end
    if iptr < @end
      len = iptr - start
      @ptr = iptr
      return String.new(start, len)
    end
    @ptr = iptr
    String.build do |io|
      io.write Slice.new(start, (@end - start).to_i)
      while (b = read_byte) && b > 32
        io.write_byte b
      end
    end
  end
  macro geti_g(name, type)
    def {{name}} : {{type}}
      trim
      iptr = @ptr
      sign = 1
      if iptr.value == 45
        sign = -1; iptr += 1
        (fill; iptr = @ptr) if @end <= iptr
      end
      n = {{type}}.zero
      while iptr + 8 <= @end
        tmp = iptr.as(UInt64*).value
        break if ((tmp &-= 0x3030303030303030_u64) & 0x8080808080808080_u64) != 0
        tmp = (tmp &* 10 &+ (tmp >> 8)) & 0x00ff00ff00ff00ff_u64
        tmp = (tmp &* 100 &+ (tmp >> 16)) & 0x0000ffff0000ffff_u64
        tmp = (tmp &* 10000 &+ (tmp >> 32)) & 0x00000000ffffffff_u64
        n = n &* 100000000 &+ tmp
        iptr += 8
      end
      while iptr < @end || (fill; iptr = @ptr; iptr < @end)
        c = iptr.value &- 48u8
        break if 9u8 < c
        n = n &* 10 &+ c
        iptr += 1
      end
      @ptr = iptr
      n &* sign
    end
  end
  geti_g(geti8, Int8); geti_g(getu8, UInt8); geti_g(geti16, Int16); geti_g(getu16, UInt16)
  geti_g(geti, Int32); geti_g(getu, UInt32); geti_g(getbi, BigInt)
  geti_g(geti64, Int64); geti_g(getu64, UInt64); geti_g(geti128, Int128); geti_g(getu128, UInt128)
  def geti32; geti; end; def getu32; getu; end
  # ---output---
  def write_byte(b : UInt8) : Nil
    flush if @optr == @oend; @optr.value = b; @optr += 1
  end
  def write(s : String) : Nil
    size = s.bytesize
    z = s.to_unsafe
    i = 0
    flush if @oend == @optr
    while @oend - @optr <= size - i
      len = @oend - @optr
      LibIOset.memcpy(@optr.as(Void*), (z + i).as(Void*), len)
      i += len
      @optr = @oend
      flush
    end
    if 0 < size - i
      LibIOset.memcpy(@optr.as(Void*), (z + i).as(Void*), size - i)
      @optr += size - i
    end
  end
  macro wi_core_g(bit)
    @[AlwaysInline]
    private def write_int_core{{bit.id}}(n1 : UInt{{bit.id}}, optr : UInt8*) : Nil
      if n1 == 0
        optr.value = 48u8
        @optr = optr + 1
        return
      end
      t_idx = 0
      while 10000 <= n1
        n0 = n1 // 10000
        REV[t_idx] = OT[n1 - n0 * 10000]
        n1 = n0
        t_idx += 1
      end
      n = n1.to_i16
      if 1000 <= n
        optr.as(UInt32*).value = OT[n]
        optr += 4
      elsif 100 <= n
        v = OT[n]
        optr[0] = (v >> 8).to_u8!
        optr[1] = (v >> 16).to_u8!
        optr[2] = (v >> 24).to_u8!
        optr += 3
      elsif 10 <= n
        v = OT[n]
        optr[0] = (v >> 16).to_u8!
        optr[1] = (v >> 24).to_u8!
        optr += 2
      else
        optr.value = 48u8 + n
        optr += 1
      end
      while 0 < t_idx
        optr.as(UInt32*).value = REV[t_idx -= 1]
        optr += 4
      end
      @optr = optr
    end
  end
  wi_core_g(8); wi_core_g(16); wi_core_g(32); wi_core_g(64); wi_core_g(128)
  macro write_int_g(bit)
    def write_int(x : Int{{bit.id}}) : Nil
      flush if @optr + 25 > @oend
      optr = @optr
      if x < 0
        optr.value = 45u8; optr += 1
        write_int_core{{bit.id}} ~x.unsafe_as(UInt{{bit.id}}) &+ 1, optr
      else
        write_int_core{{bit.id}} x.unsafe_as(UInt{{bit.id}}), optr
      end
    end
    def write_int(x : UInt{{bit.id}}) : Nil
      flush if @optr + 25 > @oend
      write_int_core{{bit.id}} x, @optr
    end
  end
  write_int_g(8); write_int_g(16); write_int_g(32); write_int_g(64)
  def write_int(x : Int128) : Nil
    flush if @optr + 45 > @oend
    optr = @optr
    if x < 0
      optr.value = 45u8; optr += 1
      write_int_core128 ~x.unsafe_as(UInt128) &+ 1, optr
    else
      write_int_core128 x.unsafe_as(UInt128), optr
    end
  end
  def write_int(x : UInt128) : Nil
    flush if @optr + 45 > @oend
    write_int_core128 x, @optr
  end
  def write_int(x : BigInt) : Nil; write x.to_s; end
  def setprecision(x) : Nil
    raise ArgumentError.new("precision shold be greater than 0 and less than 17") if x < 0 || 16 < x
    @precision = {x.to_i, 16}.min
  end
  def write_float(x : Float) : Nil
    flush if @optr + 50 > @oend
    if x < 0
      @optr.value = 45u8
      @optr += 1
      x = -x
    end
    prec = @precision
    write_int x.to_i64
    return if prec == 0
    optr = @optr
    optr.value = 46_u8
    optr += 1
    f = ((x - x.to_i64) * POW10.unsafe_fetch(prec)).to_i64
    cur = optr + prec
    while 4 <= cur - optr
      f0 = f // 10000
      rem = (f - f0 * 10000).to_i
      f = f0
      cur -= 4
      cur.as(UInt32*).value = OT[rem]
    end
    while optr < cur
      cur -= 1
      f0 = f // 10
      cur.value = (f - f0 * 10).to_u8 + 48u8
      f = f0
    end
    @optr = optr + prec
  end
  def flush : Nil
    return if @optr == @obuf
    size = @optr - @obuf
    if @out_fd < 0
      @out_io.write Slice.new @obuf, size
    else
      LibIOset.write @out_fd, @obuf.as(Void*), size
    end
    @optr = @obuf
  end
  def putv(x : Array(Array(T))) : Nil forall T
    return if x.empty?
    putv x.unsafe_fetch 0
    (1...x.size).each { |i| write_byte 10u8; putv x.unsafe_fetch i }
  end
  def putv(x : Array(Tuple)) : Nil
    return if x.empty?
    putv x.unsafe_fetch 0
    (1...x.size).each { |i| write_byte 10u8; putv x.unsafe_fetch i }
  end
  def putv(x : Int) : Nil; write_int x; end
  def putv(x : Char) : Nil; write_byte x.ord.to_u8; end
  def putv(x : Float) : Nil; write_float x; end
  def putv(x : String) : Nil; write x; end
  def putv(x : Bool) : Nil; write_byte x ? 49u8 : 48u8; end
  def putv(x : Indexable(T)) : Nil forall T
    return if x.empty?
    putv x.unsafe_fetch 0
    (1...x.size).each { |i| write_byte 32u8; putv x.unsafe_fetch i }
  end
  def print(*x) : Nil
    x.each { |v| putv v }
  end
  def outl(*x, sep : (String | Char) = ' ', endl : (String | Char) = '\n') : Nil
    if f = x.first?
      putv f
      (1...x.size).each { |i| putv sep; putv x.unsafe_fetch i }
    end
    putv endl
  end
end
