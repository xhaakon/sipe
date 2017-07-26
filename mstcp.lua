local proto = Proto("MSTCP", "MS TCP")
proto.fields.framinglen = ProtoField.uint16("MSTCP.framinglen", "TCP frame length")
proto.fields.data = ProtoField.bytes("MSTCP.data", "Data")

function dissectOne(tvbuffer, pinfo, treeitem)
  local bufferBytesLeft = (tvbuffer:len() - pinfo.desegment_offset)

  if bufferBytesLeft < 2 then
    -- Incomplete message, we don't even have the TCP framing bytes
    pinfo.desegment_len = 2 - bufferBytesLeft
    return false
  end

  local frameLenBuffer = tvbuffer(pinfo.desegment_offset, 2)
  local frameLen = frameLenBuffer:uint()
  bufferBytesLeft = bufferBytesLeft - 2

  if bufferBytesLeft < frameLen then
    pinfo.desegment_len = frameLen - bufferBytesLeft
    return false
  end

  local subtreeitem = treeitem:add(proto, tvbuffer)
  subtreeitem:add(proto.fields.framinglen, frameLenBuffer)

  local rtpbuffer = tvbuffer(pinfo.desegment_offset + 2, frameLen)
  Dissector.get("rtp"):call(rtpbuffer:tvb(), pinfo, subtreeitem)
  bufferBytesLeft = bufferBytesLeft - frameLen

  if bufferBytesLeft == 0 then
    -- Reading finished successfully 
    pinfo.desegment_offset = 0
    return false
  end

  pinfo.desegment_offset = tvbuffer:len() - bufferBytesLeft
  return true
end

function proto.dissector(tvbuffer, pinfo, treeitem)
  pinfo.cols.protocol = "MS TCP"
  while dissectOne(tvbuffer, pinfo, treeitem) do
  end

  if pinfo.desegment_len > 0 then
    pinfo.cols.protocol = "MS TCP (multi)"
  end
end

DissectorTable.get("tcp.port"):add(26129, proto)