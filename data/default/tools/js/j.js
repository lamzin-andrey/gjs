window.QtBrige = {
	/**
	 * {String} callback
	 * {String} stdout
	 * {String} stderr
	*/
	onFinish:function(callback, stdout, stderr) {
		if (window[callback] instanceof Function) {
			var out = stdout.replace(/;___PIPE___;/mg, '\n'),
				stderr = stderr.replace(/;___PIPE___;/mg, '\n');
			window[callback](out, stderr);
		}
	}
};
window.FILE_APPEND = 1;
