def shortage(x : Int, mask : Int)
  z = mask & ~x
  if z == 0
    0
  else
    ms = z.bit_length - 1
    ((x >> ms) + 1 << ms | mask & (1 << ms) - 1) - x
  end
end
