(function()
{
var memInfoApp = angular.module('memInfo',[])

memInfoApp.controller('meminfoCtrl', function( $scope, $http)
	{ 
		$http.get('cgi-bin/controller?command_name=getMemInfo').success(function(responseData)
		{
			$scope.ctrl.memtotal 	= responseData.getMemInfo.data.meminfo.MemTotal;
			$scope.ctrl.memfree 	= responseData.getMemInfo.data.meminfo.MemFree,
			$scope.ctrl.buffers 	= responseData.getMemInfo.data.meminfo.Buffers;
			$scope.ctrl.cached	 	= responseData.getMemInfo.data.meminfo.Cached;
			$scope.ctrl.swapcached= responseData.getMemInfo.data.meminfo.SwapCached;
			$scope.ctrl.active	 	= responseData.getMemInfo.data.meminfo.Active;
			$scope.ctrl.inactive 	= responseData.getMemInfo.data.meminfo.Inactive;
			$scope.ctrl.shmem		 	= responseData.getMemInfo.data.meminfo.Shmem;
		}).error(function(data, status, headers, config)
		{ 
			$scope.ctrl = [];
		});
	});
})();
