// Auto-generated. Do not edit!

// (in-package beginner_tutorials.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let geometry_msgs = _finder('geometry_msgs');

//-----------------------------------------------------------

class cmd_vel {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.robot_cmd_vel = null;
    }
    else {
      if (initObj.hasOwnProperty('robot_cmd_vel')) {
        this.robot_cmd_vel = initObj.robot_cmd_vel
      }
      else {
        this.robot_cmd_vel = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type cmd_vel
    // Serialize message field [robot_cmd_vel]
    // Serialize the length for message field [robot_cmd_vel]
    bufferOffset = _serializer.uint32(obj.robot_cmd_vel.length, buffer, bufferOffset);
    obj.robot_cmd_vel.forEach((val) => {
      bufferOffset = geometry_msgs.msg.Twist.serialize(val, buffer, bufferOffset);
    });
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type cmd_vel
    let len;
    let data = new cmd_vel(null);
    // Deserialize message field [robot_cmd_vel]
    // Deserialize array length for message field [robot_cmd_vel]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.robot_cmd_vel = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.robot_cmd_vel[i] = geometry_msgs.msg.Twist.deserialize(buffer, bufferOffset)
    }
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += 48 * object.robot_cmd_vel.length;
    return length + 4;
  }

  static datatype() {
    // Returns string type for a message object
    return 'beginner_tutorials/cmd_vel';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '156dca494411a2fd8068c53948502b64';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    geometry_msgs/Twist[] robot_cmd_vel
    
    ================================================================================
    MSG: geometry_msgs/Twist
    # This expresses velocity in free space broken into its linear and angular parts.
    Vector3  linear
    Vector3  angular
    
    ================================================================================
    MSG: geometry_msgs/Vector3
    # This represents a vector in free space. 
    # It is only meant to represent a direction. Therefore, it does not
    # make sense to apply a translation to it (e.g., when applying a 
    # generic rigid transformation to a Vector3, tf2 will only apply the
    # rotation). If you want your data to be translatable too, use the
    # geometry_msgs/Point message instead.
    
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
    const resolved = new cmd_vel(null);
    if (msg.robot_cmd_vel !== undefined) {
      resolved.robot_cmd_vel = new Array(msg.robot_cmd_vel.length);
      for (let i = 0; i < resolved.robot_cmd_vel.length; ++i) {
        resolved.robot_cmd_vel[i] = geometry_msgs.msg.Twist.Resolve(msg.robot_cmd_vel[i]);
      }
    }
    else {
      resolved.robot_cmd_vel = []
    }

    return resolved;
    }
};

module.exports = cmd_vel;
