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
  # sが存在することを仮定する
  def erase(s : Array(T)) : Nil
    node = @root
    s.each do |c|
      prev = node
      node = node.child[c]
      if (node.count -= 1) == 0
        prev.child.delete c
        break # GCパワー
      end
    end
  end
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
    s.each_with_index do |c, i|
      return i if !node.child.has_key?(c) || node.child[c].count == 1
      node = node.child[c]
    end
    s.size
  end
end
