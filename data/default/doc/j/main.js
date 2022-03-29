function main() {
	Qt.setWindowIconImage(Qt.appDir() + '/doc/i/exec.png');
	Qt.moveTo(0, 31);
	Qt.resizeTo((screen.width), (screen.height - 92));
	
	window.onresize = onResize;
	window.onkeyup = onKeyUp;
	onResize();
}
function onResize() {
	// for table
	e('contentArea').style.height = (getViewport().h - 0) + 'px';
	e('contentArea').style.maxHeight = (getViewport().h - 32) + 'px';
	setTimeout(function() {
		e('contentArea').style.height = (getViewport().h - 0) + 'px';
		e('contentArea').style['max-height'] = (getViewport().h - 32) + 'px';
	}, 1000);
	
	
}

function onKeyUp(evt) {
    if (evt.ctrlKey) {
	switch(evt.keyCode) {
	    case 79:	//O
		// onClickChangeEnv();
		break;
	    case 81:	//Q
		onClickExitMenu();
		break;
	}
	    
    }
	if (evt.keyCode == 27 && window.mainMenuIsHide) {
		Qt.showMainMenu();
	}
}

function onClickExitMenu() {
	Qt.quit();
}

window.onload = main;

