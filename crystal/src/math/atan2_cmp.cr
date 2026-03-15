# arg1 <=> arg2 (始線は0)
def atan2_cmp(y1, x1, y2, x2)
  a1 = 0 < y1 || (y1 == 0 && 0 < x1) ? 0 : 1
  a2 = 0 < y2 || (y2 == 0 && 0 < x2) ? 0 : 1
  cmp1 = a1 <=> a2
  if cmp1 != 0
    cmp1
  else
    x2 * y1 <=> x1 * y2
  end
end
