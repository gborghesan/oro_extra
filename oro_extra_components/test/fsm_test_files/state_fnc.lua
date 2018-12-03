local state, trans, conn = rfsm.state, rfsm.trans, rfsm.conn

--local variables
local iteration = 1

--parse imput parameters, if any


return function(config)

-- default config parameters
	local default_c={}
	default_c['param11']=0
	default_c['param12']=0
	default_c['param21']=0
	default_c['param22']=0
	infomsg('checking for missing parameters ...')
	local config =config or {}
	for k,v in pairs(default_c) do
		if config[k]==nil then
			config[k]=v
			infomsg(k .. ": default value assigned: " .. tostring(v))
		end
	end

	return state{
		entry =	function(fsm) 
		infomsg('value of config.param11 ' .. tostring(config.param11))
		infomsg('value of config.param21 ' .. tostring(config.param21))
		dummyfunc()
		end
	}
end	
