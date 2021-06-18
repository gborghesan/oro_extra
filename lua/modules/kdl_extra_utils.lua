local rttlib = require "rttlib"
local rtt = rtt
local kdl_extra_utils={}

kdl=require("kdlutils")


kdl_extra_utils.T={}
kdl_extra_utils.R={}

kdl_extra_utils.T.rotx=kdl.rotx
kdl_extra_utils.T.roty=kdl.roty
kdl_extra_utils.T.rotz=kdl.rotz
kdl_extra_utils.T.transl		=kdl.transl
kdl_extra_utils.R.quat			=kdl.quat
kdl_extra_utils.get_quat	=kdl.get_quat
kdl_extra_utils.T.inv				=kdl.inv
kdl_extra_utils.T.diff			=kdl.diff
kdl_extra_utils.T.addDelta	=kdl.addDelta
kdl_extra_utils.R.diff			=kdl.diff_rot
kdl_extra_utils.R.addDelta	=kdl.add_delta_rot
kdl_extra_utils.msg_to_frame	=kdl.msg_to_frame

R=rtt.provides("KDL"):provides("Rotation")
--T=rtt.provides("KDL"):provides("Frame")
--V=rtt.provides("KDL"):provides("Vector")

function kdl_extra_utils.R.rotx(r)
   return R:RotX(r)
end
function kdl_extra_utils.R.roty(r)
   return R:RotY(r)
end
function kdl_extra_utils.R.rotz(r)
   return R:RotZ(r)
end

function kdl_extra_utils.R.EulerZYX(z,y,x)
   return R:EulerZYX(z,y,x)
end

function kdl_extra_utils.R.EulerZYZ(z,y,z2)
   return R:EulerZYZ(z,y,z2)
end

function kdl_extra_utils.R.RPY(r,p,y)
   return R:RPY(r,p,y)
end


function kdl_extra_utils.T.EulerZYX(z,y,x)
  f = rtt.Variable("KDL.Frame")
  f.M=R:EulerZYX(z,y,x)
  return f
end

function kdl_extra_utils.T.EulerZYZ(z,y,z2)
  f = rtt.Variable("KDL.Frame")
  f.M=R:EulerZYZ(z,y,z2)
  return f
end
function kdl_extra_utils.T.RPY(r,p,y)
  f = rtt.Variable("KDL.Frame")
  f.M=R:RPY(r,p,y)
  return f
end

return kdl_extra_utils
