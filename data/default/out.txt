function testRead() {
	var file = "/home/x64/0helloFiles.txt",
		fh = PHP.open(file, "r"), i, s, q = '';
	ta.value += fh + "\n";
	while (!PHP.eof(fh)) {
		s = PHP.gets(fh);
		q = '';
		for (i = 0; i < s.length; i++) {
			q += s.charCodeAt(i) + ',';
		}
		ta.value += q;
	}
	alert(PHP.close(fh));
	
}

function testWrite() {
	var file = "/home/x64/0helloFiles.txt",
		fh = PHP.open(file, "w");
	if (-1 != fh) {
		PHP.puts(fh, "Mammy washinmg rammy");
	}
	
	alert(PHP.close(fh));	
}