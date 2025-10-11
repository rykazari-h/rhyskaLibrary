struct Bool;def to_i;self ? 1 : 0;end;end
macro vgen(*v);Array.new({{v[0]}}){ {% if v.size==2 %}{{v[1]}}{% else %}vgen({{*v[1..]}}){% end %} };end
macro rvgen(type,*v);{% if v.size==2 %}Array({{type}}).new({{v[0]}}){{{v[1]}}}{% else %}Array.new({{v[0]}}){rvgen({{type}},{{*v[1..]}})}{% end %};end
def putv(a : Array(T)) forall T;return if a.empty?;print a[0];(1...a.size).each{|i|putv " ";putv a[i]};end
def putv(a : Array(Array(T))) forall T;return if a.empty?;putv a[0];(1...a.size).each{|i|puts;putv a[i]};end
def putv(a : Tuple(*T)) forall T;return if a.empty?;putv a[0];(1...a.size).each{|i|putv " ";putv a[i]};end
def putv(a);print a;end
def outl;puts;end
def outl(a);putv a;puts;end
def outl(*a);putv a[0];putv " ";outl *a[1..];end
