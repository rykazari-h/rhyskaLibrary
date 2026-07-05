require "array_ext.cr"
abstract class BinaryHeap(T)
  private abstract def compare(a : T, b : T) : Bool
  @data : Array(T)
  getter data : Array(T)
  def initialize : Nil; @data = Array(T).new; end
  def initialize(z : Array(T)) : Nil; @data = z.dup; heapify; end
  def empty?; @data.empty?; end
  def size; @data.size; end
  def to_a; @data.dup; end
  def clear; @data.clear; self; end
  def reserve(cap : Int); @data.reserve(cap); self; end
  def push(val : T)
    @data << val
    up_heap @data.size - 1
    self
  end
  def <<(val : T); push(val); end
  def top
    raise IndexError.new("heap is empty") if @data.empty?
    @data.unsafe_fetch(0)
  end
  def top?; @data.first?; end
  def pop
    raise IndexError.new("heap is empty") if @data.empty?
    if @data.size == 1
      @data.pop
    else
      res = @data.unsafe_fetch(0)
      @data.unsafe_put(0, @data.pop)
      down_heap 0
      res
    end
  end
  def pop?; @data.empty? ? nil : pop; end
  def update(val : T)
    raise IndexError.new("heap is empty") if @data.empty?
    old = @data.unsafe_fetch(0)
    @data.unsafe_put(0, val)
    down_heap(0)
    old
  end
  private def up_heap(i : Int32) : Nil
    val = @data.unsafe_fetch(i)
    while 0 < i
      p = i - 1 >> 1
      break if compare(@data[p], val)
      @data.unsafe_put(i, @data.unsafe_fetch(p))
      i = p
    end
    @data.unsafe_put(i, val)
  end
  private def down_heap(i : Int32) : Nil
    val = @data.unsafe_fetch(i)
    size = @data.size
    h = size >> 1
    while i < h
      r = i + 1 << 1; l = r - 1; t = l
      t = r if r < size && compare(@data.unsafe_fetch(r), @data.unsafe_fetch(l))
      break if compare(val, @data.unsafe_fetch(t))
      @data.unsafe_put(i, @data.unsafe_fetch(t))
      i = t
    end
    @data.unsafe_put(i, val)
  end
  def heapify : Nil
    return if @data.size <= 1
    ((@data.size >> 1) - 1).downto(0) { |i| down_heap i }
  end
end
class Gpq(T) < BinaryHeap(T);private def compare(a : T, b : T) : Bool; a < b;end;end
class Lpq(T) < BinaryHeap(T);private def compare(a : T, b : T) : Bool; a > b;end;end
class Heap(T) < BinaryHeap(T)
  def initialize(&@comp : T, T -> Bool); super; end
  def initialize(z : Array(T), &@comp : T, T -> Bool); @data = z.dup; heapify; end
  private def compare(a : T, b : T) : Bool; @comp.call(a, b); end
end
