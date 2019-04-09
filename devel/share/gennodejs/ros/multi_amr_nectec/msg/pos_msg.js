// Auto-generated. Do not edit!

// (in-package multi_amr_nectec.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let geometry_msgs = _finder('geometry_msgs');

//-----------------------------------------------------------

class pos_msg {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.points2 = null;
      this.another_field2 = null;
    }
    else {
      if (initObj.hasOwnProperty('points2')) {
        this.points2 = initObj.points2
      }
      else {
        this.points2 = [];
      }
      if (initObj.hasOwnProperty('another_field2')) {
        this.another_field2 = initObj.another_field2
      }
      else {
        this.another_field2 = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type pos_msg
    // Serialize message field [points2]
    // Serialize the length for message field [points2]
    bufferOffset = _serializer.uint32(obj.points2.length, buffer, bufferOffset);
    obj.points2.forEach((val) => {
      bufferOffset = geometry_msgs.msg.Point.serialize(val, buffer, bufferOffset);
    });
    // Serialize message field [another_field2]
    bufferOffset = _serializer.uint8(obj.another_field2, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type pos_msg
    let len;
    let data = new pos_msg(null);
    // Deserialize message field [points2]
    // Deserialize array length for message field [points2]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.points2 = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.points2[i] = geometry_msgs.msg.Point.deserialize(buffer, bufferOffset)
    }
    // Deserialize message field [another_field2]
    data.another_field2 = _deserializer.uint8(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += 24 * object.points2.length;
    return length + 5;
  }

  static datatype() {
    // Returns string type for a message object
    return 'multi_amr_nectec/pos_msg';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '584ed9eab9daa1be705ab1b1de5c8229';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    geometry_msgs/Point[] points2
    uint8 another_field2
    ================================================================================
    MSG: geometry_msgs/Point
    # This contains the position of a point in free space
    float64 x
    float64 y
    float64 z
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new pos_msg(null);
    if (msg.points2 !== undefined) {
      resolved.points2 = new Array(msg.points2.length);
      for (let i = 0; i < resolved.points2.length; ++i) {
        resolved.points2[i] = geometry_msgs.msg.Point.Resolve(msg.points2[i]);
      }
    }
    else {
      resolved.points2 = []
    }

    if (msg.another_field2 !== undefined) {
      resolved.another_field2 = msg.another_field2;
    }
    else {
      resolved.another_field2 = 0
    }

    return resolved;
    }
};

module.exports = pos_msg;
