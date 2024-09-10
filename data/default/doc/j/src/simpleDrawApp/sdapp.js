window.addEventListener('load', function() {
	new SimpleEngine2D("pngCanvas", 44);
	new WaterMarkApp();
});

/**
 * @class WaterMarkApp
*/
function WaterMarkApp() {
	var o = this;
	SE2D.app = SE2D.canvas.app = this;// SE2D.setApp(this);
	SE2D.gridCell = 1; //для оптимизации расчета столкновений, 8 взято как сторона "кирпича"
	SE2D.onLoadImages = this.onInit;
	SE2D.addGraphResources([
		App.dir() + "/doc/i/exec-wp.png", "watermark"
	]);
	SE2D.onEnterFrame = function(){
		o.onEnterFrame();
	};
	
	this.BASE_W = 48;
	this.BASE_H = 48;
	
	this.canvasW = 480;
	this.canvasH = 240;
	
	this.wmX = 0;
	this.wmY = 0;
	this.wmW = this.BASE_W;
	this.wmH = this.BASE_H;
}

/**
 * @description this is WaterMarkApp
*/
WaterMarkApp.prototype.setListeners = function() {
	this.iX = e('iX');
	this.iY = e('iY');
	this.iW = e('iW');
	this.iH = e('iH');
	this.browseImage = e('browseImage');
	this.saveImage = e('saveImage');
	
	var o = this;
	
	this.browseImage.onclick = function() {
		o.onClickBrowseImage();
	}
	this.saveImage.onclick = function() {
		o.onClickSaveImage();
	}
	
	this.iX.oninput = function() {
		o.wmX = o.iX.value;
	}
	this.iY.oninput = function() {
		o.wmY = o.iY.value;
	}
	this.iW.oninput = function() {
		o.wmW = o.iW.value;
	}
	this.iH.oninput = function() {
		o.wmH = o.iH.value;
	}
	
}

WaterMarkApp.prototype.onClickSaveImage = function() {
	var file = jqlSaveFileDialog('Select png image', '*.png'),
		data,
		tmpFile;
	if (file) {
		try {
			data = SE2D.canvas.toDataURL('image/png', 1);
			FS.savePng(file, data, 9);
		} catch (err) {
			alert(err);
		}
		
	}
}

WaterMarkApp.prototype.onClickBrowseImage = function() {
	var file = jqlOpenFileDialog('Select png image', '*.png'),
		o = SE2D.app,
		tmpFile,
		tmpDir,
		cmd,
		dt = new Date(),
		batchFile = 'shell.sh',
		copyCmd = 'cp';
	if (file && FS.fileExists(file)) {
		tmpFile = App.dir() + '/tmp';
		tmpDir = tmpFile;
		this.tmpFile = tmpFile = tmpDir + '/tmp' + (dt.getTime()) + '.png';
		this.execBatch(copyCmd, (' "' + file + '" "' + tmpFile + '"'), [o, o.onFinishCopy], [o, o.onStdoutCopy], [o, o.onStderrCopy]);
	}
}
WaterMarkApp.prototype.execBatch = function(cmd, args, onFinish, onStdout, onStderr) {
	var tmpFile, 
		tmpDir = App.dir() + '/tmp',
		batchFile = 'shell.sh',
		sep = '/',
		head = '#!/bin/bash\n';
	if (!FS.fileExists('/tmp')) {
		switch (cmd) {
			case 'cp':
				cmd = 'copy';
				break;
			case 'rm':
				cmd = 'del';
				break;
		}
		head = '';
		batchFile = 'shell.bat';
		sep = '\\';
	}
	args = args.replace(/\//mig, sep);
	cmd = head + cmd + ' ' + args;
	PHP.file_put_contents(tmpDir + '/' + batchFile, cmd);
	try {
		Env.exec(tmpDir + '/' + batchFile, onFinish, onStdout, onStderr);
	} catch (ex) {
		alert(ex);
	}
	setTimeout(function(){
		if (onFinish instanceof Array){
			onFinish[1].call(onFinish[0], '', '');
		} else {
			onFinish('', '');
		}
	}, 500);
}

WaterMarkApp.prototype.onFinishCopy = function(stdout, stderr) {
	var o = SE2D.app;
	this.img = new Image();
	// this.img.setAttribute('crossOrigin', 'anonymous');
	this.img.onload = function() {
		o.onLoadSelectedImage();
		// delete o.img;
		// FS.unlink(o.tmpFile);
		// o.execBatch('rm', '"' + App.dir()  + '/tmp/*.png"', o.onStdoutCopy, o.onStdoutCopy, o.onStdoutCopy);
	}
	this.img.src = this.tmpFile;
	
}
WaterMarkApp.prototype.onStdoutCopy = function(stdout) {}
WaterMarkApp.prototype.onStderrCopy = function(stderr) {}

WaterMarkApp.prototype.onLoadSelectedImage = function() {
	var mc, k = 1;
	this.watermark.depth++;
	mc = new Sprite(this.img, 'image', this.watermark.depth - 1);
	mc.visible = 1;
	mc.depth = this.watermark.depth - 1;
	
	if (this.img.width > this.canvasW) {
		k = this.canvasW / this.img.width;
		mc.scaleX = k;
		mc.scaleY = k;
	}
	if (this.img.height * k > this.canvasH) {
		k *= this.canvasH / (this.img.height * k);
		mc.scaleX = k;
		mc.scaleY = k;
	}
	
	
	if (this.image) {
		SE2D.remove(this.image);
	}
	SE2D._root.addChild(mc);
	if (this.img.width * k < this.canvasW) {
		mc.x = this.canvasW/2 - ((this.img.width * k) / 2);
	}
	this.image = mc;
}

/**
 * @description this is SE2D
*/
WaterMarkApp.prototype.onInit = function() {
	var mc = this.app.watermark = SE2D._root.watermark;
	mc.x = 0;
	mc.y = 0;
	mc.visible = 1;
	
	this.app.setListeners();
	return;
	if (window.runUnittest && runUnittest instanceof Function) {
		runUnittest();
	}
}
/**
 * @description this is SE2D
*/
WaterMarkApp.prototype.onEnterFrame = function(event){
	try {
		
		var x = String(this.wmX) == 'undefined' ? -1 : this.wmX;
		var y = String(this.wmY) == 'undefined' ? -1 : this.wmY;
		if (x != -1 && y != -1) {
			// e('drawAppStatusBar').innerHTML = 'x = ' + x + ', y = ' + y;
			this.watermark.x = x;
			this.watermark.y = y;
			this.watermark.scaleX = (this.wmW / this.BASE_W);
			this.watermark.scaleY = (this.wmH / this.BASE_H);
		} else {
			e('drawAppStatusBar').innerHTML = 'Noth todo';
		}
	} catch (err) {
		e('drawAppStatusBar').innerHTML = err;
	}
}
