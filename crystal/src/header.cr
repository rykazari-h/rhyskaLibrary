struct Bool
    def to_i
        self ? 1 : 0
    end
end
macro vgen(*v)
    Array.new({{v[0]}}){ {% if v.size==2 %}{{v[1]}}{% else %}vgen({{*v[1..]}}){% end %} }
end
macro rvgen(type, *v)
    {% if v.size==2 %}
        Array({{type}}).new({{v[0]}}){{{v[1]}}}
    {% else %}
        Array.new({{v[0]}}){rvgen({{type}},{{*v[1..]}})}
    {% end %}
end
