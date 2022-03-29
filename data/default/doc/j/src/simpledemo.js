var Demo = {
	onClickPosOnCenter: function(){
		var w = 800, h = 600;
		Qt.moveTo( (screen.width - w) / 2, (screen.height - h) / 2);
		Qt.resizeTo(w, h);
	},
	minimize: function() {
		Qt.showNormal();
		Qt.minimize();
		
		setTimeout(function() {
			Qt.showNormal();
			Qt.minimize();
		}, 100);
	},
	runXTerm: function(){
		var o = this,
			cmd = 'xterm';
		if (!PHP.file_exists('/usr')) {
			cmd = 'notepad';
		}
		this.xtId = jexec(cmd, [o, o.onFinishXT], [o, o.onStdOutXT], [o, o.onStdErrXT]);
		
	},
	closeXTerm: function(){
		var o = this, cmd = 'kill ' + this.xtId[0];
		
		if (!PHP.file_exists('/usr')) {
			cmd = 'TASKKILL /PID ' + this.xtId[0] + ' /T';
		}
		
		this.xtId = jexec(cmd, [o, o.onFinishXT], [o, o.onStdOutXT], [o, o.onStdErrXT]);
	},
	
	onFinishXT: function(stdout, stderr) {
		e('xtStdOut').innerHTML += '<div>' + stdout + '</div>';
		e('xtStdErr').innerHTML += '<div>' + stderr + '</div>';
	},
	
	onStdOutXT: function(stdout) {
		// e('xtStdOut').innerHTML += '<div>' + stdout + '</div>';
	},
	
	onStdErrXT: function(stdout) {
		// e('xtStdErr').innerHTML += '<div>' + stdout + '</div>';
	}
};
