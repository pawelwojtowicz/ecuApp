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


ctrlApp.controller('processListCtrl', function( $scope, $http)
	{ 
		var processes = [];
		//this.processes=processList;
		$http.get('cgi-bin/controller?command_name=controller&api_name=get_process_list').success(function(data)
		{
			$scope.ctrl.processes = data.CommandExecution.Payload.processList;
			obrazek = 2 + " to jest test";
		}).error(function(data, status, headers, config)
		{ 
			$scope.processes = processList;
		});
	});
})();
