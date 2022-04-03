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
		o.outputIndex = 0;
		this.xtId = jexec(cmd, [o, o.onFinishXT], [o, o.onStdOutXT], [o, o.onStdErrXT]);
		
	},
	closeXTerm: function(){
		var o = this, cmd = 'kill ' + this.xtId[0];
		
		if (!PHP.file_exists('/usr')) {
			cmd = 'TASKKILL /PID ' + this.xtId[0] + ' /T';
		}
		o.outputIndex = 0;
		this.xtId = jexec(cmd, [o, o.onFinishXT], [o, o.onStdOutXT], [o, o.onStdErrXT]);
	},
	
	runXTerm2: function(){
		var o = this,
			cmd = 'xterm';
		if (!PHP.file_exists('/usr')) {
			cmd = 'notepad';
		}
		o.outputIndex = 2;
		this.xtId = jexec(cmd, [o, o.onFinishXT], [o, o.onStdOutXT], [o, o.onStdErrXT]);
		
	},
	closeXTerm2: function(){
		var o = this, cmd = 'kill ' + this.xtId[0];
		
		if (!PHP.file_exists('/usr')) {
			cmd = 'TASKKILL /PID ' + this.xtId[0] + ' /T';
		}
		o.outputIndex = 2;
		this.xtId = jexec(cmd, [o, o.onFinishXT], [o, o.onStdOutXT], [o, o.onStdErrXT]);
	},
    checkXTerm2: function() {
		var suffix = '2';
		if (!this.xtId) {
			e('xtStdErr' + suffix).innerHTML += '<div>Proc is not run yet.</div>';
		}
        if (PHP.isRun(this.xtId[1])) {
			e('xtStdOut' + suffix).innerHTML += '<div>Proc is run.</div>';
		} else {
			e('xtStdOut' + suffix).innerHTML += '<div>Proc is not run.</div>';
		}
    },
	onFinishXT: function(stdout, stderr) {
		var suffix = '';
		if (this.outputIndex == 2) {
			suffix = '2'
		}
		e('xtStdOut' + suffix).innerHTML += '<div>' + stdout + '</div>';
		e('xtStdErr' + suffix).innerHTML += '<div>' + stderr + '</div>';
	},
	
	onStdOutXT: function(stdout) {
		// e('xtStdOut').innerHTML += '<div>' + stdout + '</div>';
	},
	
	onStdErrXT: function(stdout) {
		// e('xtStdErr').innerHTML += '<div>' + stdout + '</div>';
	}
};
