#version 450
layout(location = 0) out vec4 outColor;

layout(push_constant) uniform Push {vec3 general; vec4 edges; vec2 cOffset;} push;



double map(double value, double inputMin, double inputMax, double outputMin, double outputMax){
	 return outputMin + (outputMax - outputMin) * ((value - inputMin) / (inputMax - inputMin));
}


void main(){
	double realZ = map(gl_FragCoord.x, 0, push.general.x, push.edges[0], push.edges[1]), imgZ = map(gl_FragCoord.y, 0, push.general.y, push.edges[2], push.edges[3]), realC = push.cOffset.x, imgC = push.cOffset.y;
	int i = -1;
	while(i < push.general[2]  && realZ * realZ + imgZ * imgZ < 4){
		double img = realZ * imgZ * 2 + imgC;
		realZ = realZ * realZ - imgZ * imgZ + realC;
		imgZ = img;
		i++;
	}
	double quotient = i / push.general[2];
	if (quotient > 0.5) outColor = vec4(0, (1 - quotient) * 1.8, 0, 1);
	else outColor  += vec4(0, quotient * 1.8, 0, 1);
}

