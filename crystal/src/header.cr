macro pt(s);pointerof({{s}});end
struct Bool;def to_i;self ? 1 : 0;end;end
macro vgen(*v);Array.new({{v[0]}}){ {% if v.size==2 %}{{v[1]}}{% else %}vgen({{v[1..].splat}}){% end %} };end
macro rvgen(type,*v);{% if v.size==2 %}Array({{type}}).new({{v[0]}}){{{v[1]}}}{% else %}Array.new({{v[0]}}){rvgen({{type}},{{v[1..].splat}})}{% end %};end
def max(a,b);a<b ? b : a;end
def min(a,b);a<b ? a : b;end
def max(*a);x=a[0];(1...a.size).each{|i|x=max(x,a[i])};x;end
def min(*a);x=a[0];(1...a.size).each{|i|x=min(x,a[i])};x;end
macro chmin(a,b);({{a}}>{{b}} ? ({{a}}={{b}};true) : false);end
macro chmax(a,b);({{a}}<{{b}} ? ({{a}}={{b}};true) : false);end
macro swap(a,b);{{a}},{{b}}={{b}},{{a}};end
def assert(cond : Bool, msg = "Assertion failed");raise msg unless cond;end
macro for(f, m, s);begin
	{{f}}
	%f = true
	loop do
		if %f;%f = false;else;{{s}};end
		break unless {{m}}
		{{yield}}
	end
end;end
