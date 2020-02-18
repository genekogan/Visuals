#ifdef GL_ES
precision mediump float;
#endif

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;
uniform float iter;

vec3 hsv(in float h, in float s, in float v) {
	return mix(vec3(1.0), clamp((abs(fract(h + vec3(3, 2, 1) / 3.0) * 6.0 - 3.0) - 1.0), 0.0 , 1.0), s) * v;
}

void main( void ) {

	vec3 p = vec3( gl_FragCoord.xy / resolution.xy, 0.0) * 2.0;
	vec4 color = vec4(0);
	float m = 1.0;
	float t = time*0.5;
	vec2 c = vec2(sin(t), cos(t));//mouse*6.28-3.14;
	float n = 3.0 + mouse.x;

	for (int i = 0; i < int(iter); i++) {
		float l = length(p); //max(abs(p.x-p.y), max(abs(p.y-p.z), abs(p.z-p.x)));
		m *= smoothstep(0.0, 1.0, l);
		p /= l*l*0.2;
		p.xy = vec2(sin(c.x)*p.x + cos(c.x)*p.y, sin(c.x)*p.y-cos(c.x)*p.x);
		p.xz = vec2(sin(c.y)*p.x + cos(c.y)*p.z, sin(c.y)*p.z-cos(c.y)*p.x);
		p = abs(mod(p, n)-n/2.0);
		
		color += vec4(hsv(l, 1.0, 1.0), 1.0);
	}

	gl_FragColor = vec4( color/float(iter) )*m;

}