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
      this.point_robot = null;
    }
    else {
      if (initObj.hasOwnProperty('point_robot')) {
        this.point_robot = initObj.point_robot
      }
      else {
        this.point_robot = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type pos_msg
    // Serialize message field [point_robot]
    // Serialize the length for message field [point_robot]
    bufferOffset = _serializer.uint32(obj.point_robot.length, buffer, bufferOffset);
    obj.point_robot.forEach((val) => {
      bufferOffset = geometry_msgs.msg.Point.serialize(val, buffer, bufferOffset);
    });
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type pos_msg
    let len;
    let data = new pos_msg(null);
    // Deserialize message field [point_robot]
    // Deserialize array length for message field [point_robot]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.point_robot = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.point_robot[i] = geometry_msgs.msg.Point.deserialize(buffer, bufferOffset)
    }
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += 24 * object.point_robot.length;
    return length + 4;
  }

  static datatype() {
    // Returns string type for a message object
    return 'multi_amr_nectec/pos_msg';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'c9ace4191c815fda1591b79a1b91a4df';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    geometry_msgs/Point[] point_robot
    
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
    if (msg.point_robot !== undefined) {
      resolved.point_robot = new Array(msg.point_robot.length);
      for (let i = 0; i < resolved.point_robot.length; ++i) {
        resolved.point_robot[i] = geometry_msgs.msg.Point.Resolve(msg.point_robot[i]);
      }
    }
    else {
      resolved.point_robot = []
    }

    return resolved;
    }
};

module.exports = pos_msg;
