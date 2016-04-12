function onCFinish(output, errors) {
	output += "\nComplete";
	if (output.length) {
		onCOut(output);
	}
	if (errors.length) {
		onCErr(errors);
	}
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
