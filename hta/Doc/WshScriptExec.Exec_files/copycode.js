function copyCodeWithSpaces(a, num) {
    try {
        var s = new Array((num ? num : 4) + 1).join(" ");
        var e = a.parentNode.parentNode.getElementsByTagName('CODE')[0],  start_text = e.textContent.replace(/^ +$/gm,""),  len1 = 0;
        start_text.replace(/^ +/gm, function (m) {if (len1 == 0 || len1 > m.length) len1 = m.length; var len = Math.floor(m.length / len1); return m; } );
        start_text = start_text.replace(/^ +/gm, function (m) {var len = Math.floor(m.length / len1); return new Array(len + 1).join("\t"); } );
        e.textContent = start_text.replace(/^\t+/gm, function (m) { var len = m.length; return new Array(len + 1).join(s); } );
        if (typeof hljs !== "undefined") hljs.highlightBlock(e);
        selectCode(a);   document.execCommand('copy');   setTimeout(clearSelection, 100);
    } catch (r){};

}

function copyCodeWithTabs(a) {
    try {
        var e = a.parentNode.parentNode.getElementsByTagName('CODE')[0],  start_text = e.textContent.replace(/^ +$/gm,""),  len1 = 0;
        start_text.replace(/^ +/gm, function (m) {if (len1 == 0 || len1 > m.length) len1 = m.length; var len = Math.floor(m.length / len1); return m; } );
        e.textContent = e.textContent.replace(/^ +$/gm,"").replace(/^ +/gm, function (m) {var len = Math.floor(m.length / len1); return new Array(len + 1).join("\t"); } );
        if (typeof hljs !== "undefined") hljs.highlightBlock(e);
        selectCode(a);   document.execCommand('copy');   setTimeout(clearSelection, 100);
    } catch (r){};
}

function copyCodeSection(a) {
    var e = a.parentNode.parentNode.getElementsByTagName('CODE')[0],  sel = document.getSelection();
    if (sel.rangeCount > 0) { var range = sel.getRangeAt(0);   var prt = range.commonAncestorContainer;
        do { if (prt.nodeName != 'CODE') prt = prt.parentNode; } while (prt.nodeName == 'SPAN');
    }
    if (e != prt) selectCode(a);
    try { document.execCommand('copy');   setTimeout(clearSelection, 100); } catch (r) {};
}


function clearSelection() {
    if (document.selection && document.selection.empty) { document.selection.empty(); }
    else if (window.getSelection) { var sel = window.getSelection();   sel.removeAllRanges(); }
}

function selectCode(a) {
    var e = a.parentNode.parentNode.getElementsByTagName('CODE')[0];                                                        // Get ID of code block
    if (window.getSelection) { var s = window.getSelection();                                                               // Not IE
        if (s.setBaseAndExtent) { var l = (e.innerText.length > 1) ? e.innerText.length - 1 : 1;
            try { s.setBaseAndExtent(e, 0, e, l); } catch (error) { selectCodeBase(e); }
        } else { selectCodeBase(e); }                                                                                       // Firefox and Opera
    }
    else if (document.getSelection) { selectCodeBase(e); }                                                                  // Some older browsers
    else if (document.selection)    { var r = document.body.createTextRange();   r.moveToElementText(e);   r.select(); }    // IE
}

function selectCodeBase(e) {
    if (window.opera && e.innerHTML.substring(e.innerHTML.length - 4) === '<BR>') { e.innerHTML = e.innerHTML + '&nbsp;'; }
    var s = document.getSelection();   var r = document.createRange();   r.selectNodeContents(e);   s.removeAllRanges();   s.addRange(r);
}
    
function setSelectionRange(input, selectionStart, selectionEnd) {
    if (input.setSelectionRange)    { input.focus();   input.setSelectionRange(selectionStart, selectionEnd); }
    else if (input.createTextRange) {
        var range = input.createTextRange();   range.collapse(true);   range.moveEnd('character', selectionEnd);   range.moveStart('character', selectionStart);   range.select(); 
    }
}

function replaceSelection (input, replaceString) {
    if (input.setSelectionRange) {
        var selectionStart = input.selectionStart;   var selectionEnd = input.selectionEnd; 
        input.value = input.value.substring(0, selectionStart) + replaceString + input.value.substring(selectionEnd);
        if (selectionStart != selectionEnd) { setSelectionRange(input, selectionStart, selectionStart + replaceString.length); }
        else { setSelectionRange(input, selectionStart + replaceString.length, selectionStart + replaceString.length); }
    }
    else if (document.selection) {
        var range = document.selection.createRange();
        if (range.parentElement() == input) {
            var isCollapsed = range.text == '';   range.text = replaceString;
            if (!isCollapsed)  { range.moveStart('character', -replaceString.length);   range.select(); }
        }
    }
}

// We are going to catch the TAB key so that we can use it, Hooray!
function catchTab(item,e){
    if (navigator.userAgent.match("Gecko")) { c = e.which; } else { c = e.keyCode; }
    if (c == 9) { replaceSelection(item, String.fromCharCode(9));   setTimeout("document.getElementById('"+item.id+"').focus();",0);   return false; }
}

function TalkToUser(qid_param) {
    var selected_text = getSelectedText();
    var quick_post_value = document.getElementsByName('req_message');
    var cur_pos = getCaretPos();
    var text = quick_post_value[0].value;
    var text_below = text.substring(0, cur_pos);
    var text_above = text.substring(cur_pos, text.length);
    var quote = '[b]' + pun_quote_authors[qid_param] + '[/b]';
    quick_post_value[0].value = text_below + quote + text_above;
    setCaretPos(text_below.length + quote.length);
}

function CodeParse(value) {
    value = value || '';
    value = value.replace(/%selectCode\(([^\)]+)\)%/ig, '<a href="#" onclick="selectCode(this); return false;" class="permalink codetitle" title="Выделяет код.">$1</a>');
    value = value.replace(/%copySection\(([^\)]+)\)%/ig, '<a href="#" onclick="copyCodeSection(this); return false;" class="permalink codetitle" title="Копирует код. Если выделен фрагмент кода, то будет скопирован фрагмент.">$1</a>');
    value = value.replace(/%copyTab\(([^\)]+)\)%/ig, '<a href="#" onclick="copyCodeWithTabs(this); return false;" class="permalink codetitle" title="Устанавливает размер отступа уровня в 1 табуляцию, после чего отформатированный код копируется.">$1</a>');
    value = value.replace(/%copySpace(\d)\(([^\)]+)\)%/ig, '<a href="#" onclick="copyCodeWithSpaces(this, $1); return false;" class="permalink codetitle" title="Устанавливает размер отступа уровня в $1 пробела, после чего отформатированный код копируется.">$2</a>');
    value = value.replace(/%(bottom|top)%/ig, ' style="border-$1:1px #CCC solid; white-space: nowrap !important;"');
    $('.codebox').each(function(i,elem){ code = value.split("%code%").join($(elem).html());   $(elem).html(code); });
}


// add auto prefix (author JSman)
document.addEventListener("DOMContentLoaded", function(event) {
    if (!document.querySelector("*[name=req_subject]")) return;
    let prefixes = {
        "13": "AHK",
        "27": "AHK",
        "14": "WSH,VBS,JS",
        "17": "VBA",
        "21": "JS",
        "18": "CMD/BAT",
        "8": "OFF"
    }
    let e = document.querySelector("*[name=req_subject]");
    if (!e.value) e.value = location.href.replace(/^.*fid=(\d+)/, (m, id) => prefixes[id]?prefixes[id]+": ":"");
});