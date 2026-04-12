struct Range(B, E)
  # operator(|&^-)を離散値集合について定義する
  # 返り値は閉区間である
  def |(other : Range(B, E)) : Range(B, E) | {Range(B, E), Range(B, E)}
    b1, e1 = self.begin, self.exclusive? ? self.end - 1 : self.end
    b2, e2 = other.begin, other.exclusive? ? other.end - 1 : other.end
    if b1 <= e2.succ && b2 <= e1.succ
      (b1 < b2 ? b1 : b2)..(e1 > e2 ? e1 : e2)
    else
      r1, r2 = b1..e1, b2..e2
      b1 < b2 ? {r1, r2} : {r2, r1}
    end
  end
  def &(other : Range(B, E)) : Range(B, E)?
    b1, e1 = self.begin, self.exclusive? ? self.end - 1 : self.end
    b2, e2 = other.begin, other.exclusive? ? other.end - 1 : other.end
    b = b1 > b2 ? b1 : b2
    e = e1 < e2 ? e1 : e2
    if b <= e
      b..e
    else
      nil
    end
  end
  def ^(other : Range(B, E)) : {Range(B, E)?, Range(B, E)}
    b1, e1 = self.begin, self.exclusive? ? self.end - 1 : self.end
    b2, e2 = other.begin, other.exclusive? ? other.end - 1 : other.end
    if e2 < b1 || e1 < b2
      r1, r2 = b1..e1, b2..e2
      b1 < b2 ? {r1, r2} : {r2, r1}
    else
      b1, b2 = b2, b1 if b2 < b1
      e1, e2 = e2, e1 if e2 < e1
      {b1 < b2 ? b1..b2.pred : nil, e1 < e2 ? e2.succ..e2 : nil}
    end
  end
  def -(other : Range(B, E)) : {Range(B, E)?, Range(B, E)}
    b1, e1 = self.begin, self.exclusive? ? self.end - 1 : self.end
    b2, e2 = other.begin, other.exclusive? ? other.end - 1 : other.end
    if e2 < b1 || e1 < b2
      {b1..e1, nil}
    elsif b2 <= b1 && e1 <= e2
      {nil, nil}
    else
      {b1 < b2 ? b1..b2.pred : nil, e2 < e1 ? e2.succ..e1 : nil}
    end
  end
end
