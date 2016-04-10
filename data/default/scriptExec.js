function onOut(s) {
	document.getElementById('out').innerHTML =  document.getElementById('out').innerHTML + '<div style="color:blue">' + s + '</div>';
}
function onErr(s) {
	document.getElementById('out').innerHTML =  document.getElementById('out').innerHTML + '<div style="color:red">' + s + '</div>';
}
function executeCommand() {
	//var path = Qt.appDir() + "/out.txt";
	//var n = PHP.file_put_contents(path, document.getElementById('in').value);
	
	var s = document.getElementById('epath').value;
	//alert('will run ' + s);
	PHP.exec(s, 'onOut', 'onErr');
}


//========================================
function onCFinish(output, errors) {
	alert('Out: ' + output.replace(/;___PIPE___;/mg, '\n'));
	alert('Errors: ' + errors.replace(/;___PIPE___;/mg, '\n'));
}
function onCOut(s) {
	document.getElementById('cout').innerHTML =  document.getElementById('cout').innerHTML + '<div style="color:blue">' + s + '</div>';
}
function onCErr(s) {
	document.getElementById('cout').innerHTML =  document.getElementById('cout').innerHTML + '<div style="color:red">' + s + '</div>';
}
function executeCCommand() {
	var s = document.getElementById('cepath').value;
	PHP.execCProcess(s, 'onCFinish', 'onCOut', 'onCErr');
}
