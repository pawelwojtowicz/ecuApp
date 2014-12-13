(function()
{
var ctrlApp = angular.module('controller',[])

var processList = [
									{
									'name':'exampleApp',
									'versionInfo': '20141212-build01',
									'unitState':'iddle'
									},
									{
									'name':'testApp',
									'versionInfo': '20141212-build01',
									'unitState':'busy'
									},
									{
									'name':'exampleApp',
									'versionInfo': '20141212-build01',
									'unitState':'stopped'
									}
									];

ctrlApp.controller('processListCtrl', function(){ this.processes=processList;});

})();
