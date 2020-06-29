
function get_dateset(opt) {
	$.get(window.stat_server + "/dataset.stat?dataset=" + opt,function(data,status){
		//alert("数据: " + data + "\n状态: " + status + "\nsize:" + data.length);
		var ctx = document.getElementById('canvas').getContext('2d');
		window.myBar = new Chart(ctx, {
			type: window.showstyle,
			data: barChartData,
			options: {
				responsive: true,
				legend: {
					position: 'top',
				},
				title: {
					display: true,
					text: '数据统计模板示例'
				},
				scales: {
					yAxes: [{
						ticks: {
						   // beginAtZero: true,
							min: 100
						},
					}]
				}
			}
		});
			
		var obj = JSON.parse(data);
		barChartData.labels.splice(0,barChartData.labels.length);
		barChartData.datasets.splice(0,barChartData.datasets.length);
				
		var color = Chart.helpers.color;
		var colorNames = Object.keys(window.chartColors);
		var haslabel = false;
		var counts = 0;
		for(var itemkey in obj){
			counts=counts+1;
			var colorName = colorNames[counts % colorNames.length];
	        var dsColor = window.chartColors[colorName];
			var newDataset = {
				label: itemkey,
				backgroundColor: color(dsColor).alpha(0.5).rgbString(),
				borderColor: dsColor,
				borderWidth: 1,
				data: [],
				fill: false
			};
			var itemobj = obj[itemkey];
			for(var key in itemobj){
				if(!haslabel) {
					barChartData.labels.push(key);
				}
				newDataset.data.push(parseInt(itemobj[key]));
			}
			barChartData.datasets.push(newDataset);
			haslabel = true;
		}
				
		window.myBar.update();
	});
};

function onselect_dateset() {
	var opt=$("#dateset").val();
	var itemtypeopt=$("#itemtypeselect").val();
	if(itemtypeopt == "ruleid" || itemtypeopt == "tagid") {
		var opt_rlt = opt+"_0,"+opt+"_1";
		opt = opt+"," + opt_rlt;
	}
	get_dateset(opt);
};

function gettypelist() {
	$.get(window.stat_server + "/category.list",function(data,status){
		//alert("数据: " + data + "\n状态: " + status + "\nsize:" + data.length);
		var obj = JSON.parse(data);
		var selectlist = "<select id='itemtypeselect' name='itemtypeselect' onchange='get_item_name_list()'>"; 
		for(var itemkey in obj){
			selectlist += "<option value='" +itemkey+ "'>" + itemkey + "</option>"; 
		}	
		selectlist += "</select>"; 
		//document.getElementById('addControl').innerHTML =selectlist;
		$('#typelist').html(selectlist);
			
	});
};

function onselect_showstype() {
	window.showstyle=$("#showstyle").val();
};

function insert_showstype() {
	var showstyle = "<select id='showstyle' name='showstyle' onchange='onselect_showstype()'><option value='line'>line</option><option value='bar'>bar</option></select>"; 
	$('#showstylearea').html(showstyle);
};

function get_item_name_list() {
	var opt=$("#itemtypeselect").val();
		$.get(stat_server + "/dataset.list?category=" + opt,function(data,status){
		//alert("数据: " + data + "\n状态: " + status + "\nsize:" + data.length);
		var obj = JSON.parse(data);
		var selectlist = "<select id='dateset' name='dateset' onchange='onselect_dateset()'>"; 
		for(var itemkey in obj){
			selectlist += "<option value='" +itemkey+ "'>" + itemkey + "</option>"; 
		}	
		selectlist += "</select>"; 
		//document.getElementById('addControl').innerHTML =selectlist;
		$('#datesetlist').html(selectlist);
		
		onselect_dateset();

		//window.myBar.update();
		});
};


		var MONTHS = ['January', 'February', 'March', 'April', 'May', 'June', 'July', 'August', 'September', 'October', 'November', 'December'];
		var color = Chart.helpers.color;
		var barChartData = {
			labels: [],
			datasets: []

		};

		window.onload = function() {
			
			window.showstyle = 'line';
			window.stat_server = "http://182.92.221.32:29807"//'http://192.168.196.129:29056';
			$.get(window.stat_server + "/dataset.stat?dataset=pv,uv",function(data,status){
				//alert("数据: " + data + "\n状态: " + status + "\nsize:" + data.length);
				var ctx = document.getElementById('canvas').getContext('2d');
				window.myBar = new Chart(ctx, {
					type: window.showstyle,
					data: barChartData,
					options: {
						responsive: true,
						legend: {
							position: 'top',
						},
						title: {
							display: true,
							text: '数据统计模板示例'
						},
						scales: {
							yAxes: [{
								ticks: {
								   // beginAtZero: true,
									min: 100
								},
								
							}]
						}
					}
				});
			
				var obj = JSON.parse(data);
				barChartData.labels.splice(0,barChartData.labels.length);
				barChartData.datasets.splice(0,barChartData.datasets.length);
				var colorNames = Object.keys(window.chartColors);
				var haslabel = false;
				var counts = 0;
				for(var itemkey in obj){
					counts=counts+1;
					var colorName = colorNames[counts % colorNames.length];
			        var dsColor = window.chartColors[colorName];
					var newDataset = {
						label: itemkey,
						backgroundColor: color(dsColor).alpha(0.5).rgbString(),
						borderColor: dsColor,
						borderWidth: 1,
						data: [],
						fill: false
					};
					var itemobj = obj[itemkey];
					for(var key in itemobj){
						if(!haslabel) {
							barChartData.labels.push(key);
						}
						newDataset.data.push(parseInt(itemobj[key]));
					}
					barChartData.datasets.push(newDataset);
					haslabel = true;
				}
				
				window.myBar.update();
				insert_showstype();
				gettypelist();
			});

		};
		
		