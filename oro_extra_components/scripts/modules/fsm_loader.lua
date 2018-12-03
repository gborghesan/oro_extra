local fsm_loader ={}


function fsm_loader.file_exists(name)
   local f=io.open(name,"r")
   if f~=nil then io.close(f) return true else return false end
end


function fsm_loader.load_rfsm(file,config)
    if errmsg==nil then errmsg=print; 
  end
  local config = config or nil
  if not fsm_loader.file_exists(file) then print("error, file " .. file .. "  does not exist") return false, 'error, ' .. file end
  local chunk  = loadfile(file)
  if chunk==nil then errmsg("error, file `" .. file .. "` is ill-formed") return false end
  local getfsm = chunk()
  if type(getfsm) == 'function' then
    local fsm    = getfsm(config)
    if not rfsm.is_state(fsm) then
      return false, 'error, FSM not found in '..file
    end
    return fsm
  end
  if type(getfsm) == 'table' then
    return getfsm
  end
  return false, file..' corrupted'
end

return fsm_loader
