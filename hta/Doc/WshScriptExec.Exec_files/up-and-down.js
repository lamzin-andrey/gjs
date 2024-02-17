jQuery(function(){
	$("#pan_top").hide().removeAttr("href");
	if ($(window).scrollTop()>="200") $("#pan_top").fadeIn("slow");
		$(window).scroll(function(){
	if ($(window).scrollTop()<="200") $("#pan_top").fadeOut("slow");
	else $("#pan_top").fadeIn("slow");
	});

	$("#pan_bottom").hide().removeAttr("href");
	if ($(window).scrollTop()<=$(document).height()-"999") $("#pan_bottom").fadeIn("slow");
		$(window).scroll(function(){
	if ($(window).scrollTop()>=$(document).height()-"999") $("#pan_bottom").fadeOut("slow");
	else $("#pan_bottom").fadeIn("slow");
	});

	$("#pan_top").click(function(){
	$("html, body").animate({scrollTop:0},"slow");
	});
	$("#pan_bottom").click(function(){
	$("html, body").animate({scrollTop:$(document).height()},"slow");
	});
});