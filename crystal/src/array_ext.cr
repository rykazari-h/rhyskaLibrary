class Array(T)
  # capacityをcap以上に変更する
  def reserve(cap : Int)
    resize_to_capacity(@offset_to_buffer + cap) if @capacity < @offset_to_buffer + cap
    self
  end
  def unsafe_resize(n : Int)
    raise ArgumentError.new("Negative array size") if n < 0
    if n < @size
      self.delete_at n, @size - n
    else
      ncap = @offset_to_buffer + n
      resize_to_capacity(ncap) if @capacity < ncap
      z = @buffer + @size
      @size = n
    end
    self
  end
  def resize(n : Int, v : T)
    raise ArgumentError.new("Negative array size") if n < 0
    if n < @size
      self.delete_at n, @size - n
    else
      ncap = @offset_to_buffer + n
      resize_to_capacity(ncap) if @capacity < ncap
      z = @buffer + @size
      (n - @size).times  { |i| z[i] = v }
      @size = n
    end
    self
  end
  def unique!
    return self if empty?
    fi = 0
    z = @buffer
    val = z[0]
    i = 1
    while i < @size
      if z[i] != val
        z[fi] = val
        fi += 1
        val = z[i]
      end
      i += 1
    end
    z[fi] = val
    fi += 1
    self.delete_at(fi, @size - fi)
    self
  end
  def unique
    clone.unique!
  end
  def reverse!(l : Int = 0, r : Int = @size)
    reverse! @buffer + l, @buffer + r
  end
  def reverse!(pl : Pointer(T), pr : Pointer(T))
    pr -= 1
    while pl < pr
      tmp = pl.value
      pl.value = pr.value
      pr.value = tmp
      pl += 1
      pr -= 1
    end
    self
  end
  def next_permutation(l = 0, r = @size)
    return false if r <= l + 1
    first = @buffer + l
    last = @buffer + r
    i = last - 1
    while first < i
      ni = i
      i -= 1
      if i.value < ni.value
        j = last
        loop do
          j -= 1
          break if i.value < j.value
        end
        tmp = i.value
        i.value = j.value
        j.value = tmp
        reverse! ni, last
        return true
      end
    end
    reverse! first, last
    return false
  end
  def prev_permutation(l = 0, r = @size)
    return false if r <= l + 1
    first = @buffer + l
    last = @buffer + r
    i = last - 1
    while first < i
      ni = i
      i -= 1
      if i.value > ni.value
        j = last
        loop do
          j -= 1
          break if i.value > j.value
        end
        tmp = i.value
        i.value = j.value
        j.value = tmp
        reverse! ni, last
        return true
      end
    end
    reverse! first, last
    return false
  end
end
