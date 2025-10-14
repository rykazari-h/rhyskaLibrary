class Array(T)
def unique;return [] of T if empty?;fi = 0;arr = self.clone;val = arr[0];(1...size).each{|i|;if arr[i] != val;arr[fi] = val;fi += 1;val = arr[i];end;};arr[fi] = val;fi += 1;arr[0...fi];end
def unique!;return self if empty?;fi = 0;val = self[0];(1...size).each{|i|;if self[i] != val;self[fi] = val;fi += 1;val = self[i];end;};self[fi] = val;fi += 1;self.replace(self[0, fi]);self;end
end
