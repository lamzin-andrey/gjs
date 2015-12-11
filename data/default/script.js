function save() {
	var path = Qt.appDir() + "/out.txt";
	var n = PHP.file_put_contents(path, document.getElementById('in').value);
	alert(n);
}
