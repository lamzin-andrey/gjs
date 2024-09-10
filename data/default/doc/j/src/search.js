window.Search = {
	init:function() {
		var o = this;
		o.inputSearch = e('iFilter');
		o.hResults = e('hResults');
		o.hContentArea = e('contentArea');
		o.setListeners();
	},
	setListeners:function() {
		var o = this;
		o.inputSearch.oninput = function(event) {
			o.onInputText(event);
		}
		o.inputSearch.onkeyup = function(event) {
			o.onInputText(event);
		}
	},
	onInputText:function(event) {
		var o = this;
		if (o.inputSearch.value.length > 3 || o.inputSearch.value.length == 0 || event.keyCode == 13) {
			
			try {
				o.filterResults(o.inputSearch.value);
			} catch (err) {
				alert(err);
			}
		}
	},
	filterResults:function(searchStr) {
		var o = this, br = 0, i, j = 0;
		o.offset = 0;
		o.resultsIdList = {};
		while (-1 != o.offset) {
			o.filterOneResult(searchStr);
			br++;
			if (br > 500) {
				alert(L('Ничего не найдено, аварийный выход'));
				break;
			}
			continue;
		}
		for (i in o.resultsIdList) {
			j++;
			// alert(i);
		}
		
		o.renderResultsList();
		
		if (!searchStr) {
			// TODO
			o.renderResultsList(true);
		}
		
	},
	renderResultsList:function(showAll) {
		var i,
			o = this,
			ls = o.hResults.getElementsByTagName('a'),
			id;
		for (i = 0; i < ls.length; i++) {
			id = ls[i].getAttribute('href').replace('#', '');
			if (!o.resultsIdList[id] && !showAll) {
				ls[i].parentNode.style.display = 'none';
			} else {
				ls[i].parentNode.style.display = 'block';
			}
		}
	},
	
	filterOneResult:function(searchStr) {
		var o = this, searchIndex, openIndex, closeIndex, functionId, 
			html = o.hContentArea.innerHTML.toLowerCase(),
			sourceHtml = o.hContentArea.innerHTML;
		searchStr = searchStr.toLowerCase();
		if (!searchStr) {
			o.offset = -1;
			return -1;
		}
		// Найти вхождение в html
		searchIndex = html.indexOf(searchStr, o.offset);
		// Если оно есть, проверить, что идет после вхождения раньше, < или >
		if (-1 == searchIndex) {
			o.offset = searchIndex;
			return -1;
		}
		o.offset = searchIndex + 1;
		openIndex = html.indexOf('<', searchIndex);
		closeIndex = html.indexOf('>', searchIndex);
		if (-1 == openIndex || -1 == closeIndex) {
			return -1;
		}
		// Если > идет раньше, чем < считать результат не валидным
		if (openIndex > closeIndex) {
			return -1;
		}
		// Если результат валидный, найти div.function предшевствующий вхождению и сохранить его id
		functionId = o.getFunctionId(sourceHtml, searchIndex);
		if (functionId) {
			o.resultsIdList[functionId] = 1;
		}
		//  также найти первый h5 и h4 предшевствующий div.function и сохранить их id
		h5IdData = o.getH5Id(sourceHtml, searchIndex);
		if (h5IdData.id) {
			o.resultsIdList[h5IdData.id] = 1;
			h4Id = o.getH4Id(sourceHtml, h5IdData.index);
			if (h4Id) {
				o.resultsIdList[h4Id] = 1;
			}
		} else {
			h4Id = o.getH4Id(sourceHtml, searchIndex);
			if (h4Id) {
				o.resultsIdList[h4Id] = 1;
			}
		}
		
		return 0;
	},
	getFunctionId:function(html, searchIndex){
		var classIndex = html.lastIndexOf('class="function', searchIndex),
			idToken = '<div id="',
			quote = '"',
			start,
			end;
		if (classIndex != -1) {
			start = html.lastIndexOf(idToken, classIndex);
			end = html.lastIndexOf(quote, classIndex)
			if (end > start && -1 !== end) {
				return html.substring(start + idToken.length, end);
			}
		}
		
		return '';
	},
	/**
	 * @return Object {id:String, index:Number}
	*/
	getH5Id:function(html, searchIndex){
		var token = '<h5 id="',
			start = html.lastIndexOf(token, searchIndex),
			quote = '"',
			start,
			end,
			result = {};
		if (start != -1) {
			end = html.indexOf(quote, start + token.length)
			if (end > start && -1 !== end) {
				result.id = html.substring(start + token.length, end);
				result.index = start;
				return result;
			}
		}
		result.id = '';
		return result;
	},
	/**
	 * @return String
	*/
	getH4Id:function(html, searchIndex){
		var token = '<h4 id="',
			start = html.lastIndexOf(token, searchIndex),
			quote = '"',
			start,
			end;
		if (start != -1) {
			end = html.indexOf(quote, start + token.length)
			if (end > start && -1 !== end) {
				return html.substring(start + token.length, end);
			}
		}
		return '';
	}
};
