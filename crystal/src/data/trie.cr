class Trie(T)
  class Node(T)
    property child : Hash(T, Node(T))
    property count : Int32
    def initialize
      @child = Hash(T, Node(T)).new
      @count = 0
    end
  end
  def initialize;@root = Node(T).new;end
  def insert(s : String);insert s.chars;end
  def lcp(s : String);lcp s.chars;end
  def insert(s : Array(T)) : Nil
    node = @root
    s.each do |c|
      node.child[c] = Node(T).new unless node.child.has_key? c
      node = node.child[c]
      node.count += 1
    end
  end
  def lcp(s : Array(T)) : Int32
    node = @root
    s.size.times do |i|
      return i if !node.child.has_key?(s[i]) || node.child[s[i]].count == 1
      node = node.child[s[i]]
    end
    s.size
  end
end
