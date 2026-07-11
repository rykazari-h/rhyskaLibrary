module RadixSort
  def self.sort(arr : Array(T)) : Array(T) forall T
    sort! arr.dup
  end
  def self.sort!(arr : Array(T)) : Array(T) forall T
    n = arr.size
    return arr if n <= 1
    buf = Array(T).new(n, T.zero)
    # 基数0x100
    {% if T == Int8 %}
      n.times { |i| arr.unsafe_put(i, arr.unsafe_fetch(i) ^ 0x80u32) }
      sort_internal(n, 1, arr.to_unsafe.as(Pointer(UInt8)), buf.to_unsafe.as(Pointer(UInt8)))
      arr = buf
      n.times { |i| arr.unsafe_put(i, arr.unsafe_fetch(i) ^ 0x80u32) }
    {% elsif T == UInt8 %}
      sort_internal(n, 1, arr.to_unsafe, buf.to_unsafe)
      arr = buf
    {% elsif T == Int16 %}
      n.times { |i| arr.unsafe_put(i, arr.unsafe_fetch(i) ^ 0x8000u32) }
      sort_internal(n, 2, arr.to_unsafe.as(Pointer(UInt16)), buf.to_unsafe.as(Pointer(UInt16)))
      n.times { |i| arr.unsafe_put(i, arr.unsafe_fetch(i) ^ 0x8000u32) }
    {% elsif T == UInt16 %}
      sort_internal(n, 2, arr.to_unsafe, buf.to_unsafe)
    {% elsif T == Int32 %}
      n.times { |i| arr.unsafe_put(i, arr.unsafe_fetch(i) ^ 0x80000000u32) }
      sort_internal(n, 4, arr.to_unsafe.as(Pointer(UInt32)), buf.to_unsafe.as(Pointer(UInt32)))
      n.times { |i| arr.unsafe_put(i, arr.unsafe_fetch(i) ^ 0x80000000u32) }
    {% elsif T == UInt32 %}
      sort_internal(n, 4, arr.to_unsafe, buf.to_unsafe)
    {% elsif T == Int64 %}
      n.times { |i| arr.unsafe_put(i, arr.unsafe_fetch(i) ^ 0x8000000000000000u64) }
      sort_internal(n, 8, arr.to_unsafe.as(Pointer(UInt64)), buf.to_unsafe.as(Pointer(UInt64))))
      n.times { |i| arr.unsafe_put(i, arr.unsafe_fetch(i) ^ 0x8000000000000000u64) }
    {% elsif T == UInt64 %}
      sort_internal(n, 8, arr.to_unsafe, buf.to_unsafe)
    {% elsif T == Int128 %}
      n.times { |i| arr.unsafe_put(i, arr.unsafe_fetch(i) ^ 0x80000000000000000000000000000000u128) }
      sort_internal(n, 16, arr.to_unsafe.as(Pointer(UInt128)), buf.to_unsafe.as(Pointer(UInt128)))
      n.times { |i| arr.unsafe_put(i, arr.unsafe_fetch(i) ^ 0x80000000000000000000000000000000u128) }
    {% else %}
      sort_internal(n, 16, arr.to_unsafe, buf.to_unsafe)
    {% end %}
    arr
  end
  def self.sort_by(arr : Array(T), & : T -> K) forall T, K
    n = arr.size
    return arr if n <= 1
    z = Pointer(K).malloc(n) { |i| yield arr.unsafe_fetch(i) }
    buf = Pointer(Int32).malloc(n)
    idx = Pointer(Int32).malloc(n) { |i| i }
    # 基数0x100
    {% if K == Int8 %}
      n.times { |i| z.unsafe_put(i, z.unsafe_fetch(i) ^ 0x80u32) }
      sort_by_internal(n, idx, 1, z.to_unsafe.as(Pointer(UInt8)), buf)
      idx = buf
    {% elsif K == UInt8 %}
      sort_by_internal(n, idx, 1, z.to_unsafe, buf)
      idx = buf
    {% elsif K == Int16 %}
      n.times { |i| z.unsafe_put(i, z.unsafe_fetch(i) ^ 0x8000u32) }
      sort_by_internal(n, idx, 2, z.to_unsafe.as(Pointer(UInt16)), buf)
    {% elsif K == UInt16 %}
      sort_by_internal(n, idx, 2, z.to_unsafe, buf)
    {% elsif K == Int32 %}
      n.times { |i| z.unsafe_put(i, z.unsafe_fetch(i) ^ 0x80000000u32) }
      sort_by_internal(n, idx, 4, z.to_unsafe.as(Pointer(UInt32)), buf)
    {% elsif K == UInt32 %}
      sort_by_internal(n, idx, 4, z.to_unsafe, buf)
    {% elsif K == Int64 %}
      n.times { |i| z.unsafe_put(i, z.unsafe_fetch(i) ^ 0x8000000000000000u64) }
      sort_by_internal(n, idx, 8, z.to_unsafe.as(Pointer(UInt64)), buf)
    {% elsif K == UInt64 %}
      sort_by_internal(n, idx, 8, z.to_unsafe, buf)
    {% elsif K == Int128 %}
      n.times { |i| z.unsafe_put(i, z.unsafe_fetch(i) ^ 0x80000000000000000000000000000000u128) }
      sort_by_internal(n, idx, 16, z.to_unsafe.as(Pointer(UInt128)), buf)
    {% else %}
      sort_by_internal(n, idx, 16, z.to_unsafe, buf)
    {% end %}
    Array(T).new(n) { |i| arr[idx[i]] }
  end
  def self.sort_by!(arr : Array(T), &block : T -> K) forall T, K
    arr = sort_by(arr, &block)
  end
  def self.sort_by_internal(n : Int32, z1 : Pointer(Int32), t : Int32, val : Pointer(U), z2 : Pointer(Int32)) forall U
    count = Pointer(Int32).malloc(256, 0)
    t.times do |pos|
      shift = pos << 3
      256.times { |i| count[i] = 0 }
      n.times { |i| count[val[i] >> shift & 255] += 1 }
      # 0, c0, (c0+c1), ...
      # 各値のbeginning
      tot = 0
      256.times do |i|
        old = count[i]
        count[i] = tot
        tot += old
      end
      n.times do |j|
        i = z1[j]
        v = val[i] >> shift & 255
        z2[count[v]] = i
        count[v] += 1
      end
      tmp = z1
      z1 = z2
      z2 = tmp
    end
  end
  def self.sort_internal(n : Int32, t : Int32, z1 : Pointer(U), z2 : Pointer(U)) forall U
    count = Pointer(Int32).malloc(256, 0)
    t.times do |pos|
      shift = pos << 3
      256.times { |i| count[i] = 0 }
      n.times { |i| count[z1[i] >> shift & 255] += 1 }
      # 0, c0, (c0+c1), ...
      # 各値のbeginning
      tot = 0
      256.times do |i|
        old = count[i]
        count[i] = tot
        tot += old
      end
      n.times do |i|
        val = z1[i] >> shift & 255
        z2[count[val]] = z1[i]
        count[val] += 1
      end
      tmp = z1
      z1 = z2
      z2 = tmp
    end
  end
end
