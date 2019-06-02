function R = parallel(varargin)
  R = 1 / sum(1 ./ [varargin{:}]);
end
