(function()
{
var ctrlApp = angular.module('controller',[])

ctrlApp.controller('processListCtrl', function( $scope, $http)
	{ 
		$http.get('cgi-bin/controller?command_name=controller&api_name=get_process_list').success(function(responseData)
		{
			$scope.ctrl.processes = responseData.get_process_list.data.processList;
		}).error(function(data, status, headers, config)
		{ 
			$scope.processes = processList;
		});
	});
})();
