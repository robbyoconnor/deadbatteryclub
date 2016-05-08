
module cr2032(dia=20, height=3.2, ax=0.8, zx=0.3) {
	cylinder(r=(dia + ax)/2, h=(height + zx), $fn=100);
	//cube([dia+ax, dia+ax, height + zx],center=true);
}

module hole(dia=0.8) {
	cylinder(r=dia/2, h=50, center=true);
}

module radrect(l, w, h, r) {
	translate([0,0,h/2]) 
		union() {
			cube([l-2*r, w, h],center=true);
			cube([l, w-2*r, h],center=true);
			translate([-(l/2-r),-(w/2-r),0]) 
				cylinder(r=r, h=h, $fn=40, center=true);
			translate([-(l/2-r),(w/2-r),0]) 
				cylinder(r=r, h=h, $fn=40, center=true);
			translate([(l/2-r),-(w/2-r),0]) 
				cylinder(r=r, h=h, $fn=40, center=true);
			translate([(l/2-r),(w/2-r),0]) 
				cylinder(r=r, h=h, $fn=40, center=true);
		}
}

module can(length = 48, width=23, height = 10, lid_height=1.5,
				tab_height=5) {
	radrect(length, width, height, 6.5);
	if (height > 5) {
	translate([0,0,height-lid_height])
		radrect(length + 2.4, width + 2.4, lid_height, 6.5);

	translate([0,0,height-tab_height])
	difference() {
		translate([-length/2, 0, 0])
			radrect(12*2,15,tab_height,5);
		union() {
			translate([-(length/2 + 6), 0, 0])
				cylinder(r=5/2, h=height);
			translate([-length/2 - 2.4, -width/2, tab_height-0.5])
				cube([2.4,width,0.5]);
		}
	}
}
}

module esp(length=25.2, width=14.7, height=3, a=1, az=0) {
	translate([0,0,(height+az)/2]) 
		cube([length+a, width+a, height+az],center=true);
}

module tact(length=9, width=5, height=3) {
	translate([0,0,height/2]) 
		cube([width, length, height], center=true);
}

module windowtact(height=3, extra=5) {
	tact(height=height+extra);
}

//hs = 1.5;
//if (false) 
//difference() {
//	cube([30,8,5],center=true);
//	union() {
//		cr2032();
//		translate([hs, hs, 0]) hole();
//		translate([hs, -hs, 0]) hole();
//		translate([-hs, hs, 0]) hole();
//		translate([-hs, -hs, 0]) hole();
//		
//		//top cavity
//	}
//}

module pcb(length=14+2,width=15.5,thick=1.7) {
	translate([0,0,thick/2])
			cube([length,width,thick], center=true);
	translate([0,0,-(3-thick)/2])
			cube([length,width-4,3-thick], center=true);

}

module windowled(l=8,w=4+4,h=10) {
	translate([0,0,h/2])
		cube([w,l,h],center=true);
}

base = 2;
top = 2;
esp_height = 3;
pcb_thick = 1.7;
pcb_shelf = base + esp_height + 0.5 - pcb_thick;
pcb_top = pcb_shelf + pcb_thick;

rotate([0,180,0])
difference() 
					{
	can(height = 10);
//	can(height=base);
//translate([0,0,10-top])
//	can(height=top);

	union() {

		translate([0,0,pcb_top])
			cr2032();
		translate([2,0,pcb_top+1])
			cr2032();
		translate([4,0,pcb_top+2])
			cr2032();
		translate([6,0,pcb_top+3])
			cr2032();
		translate([0,0,pcb_top-1])
			cr2032();
		

		translate([8,0,base]) esp();		
		translate([8 - 4,0,base + 1]) esp();		


//		translate([0,0,-2])
//			/*PCB*/ translate([-13.5,0,1])cube([14,15.5,2], center=true);
		translate([-13.5+1,0,pcb_shelf])
			pcb();	

		translate([-18,0,pcb_top]) windowtact();
		translate([-13,0,pcb_top]) windowled();	

	}
}
