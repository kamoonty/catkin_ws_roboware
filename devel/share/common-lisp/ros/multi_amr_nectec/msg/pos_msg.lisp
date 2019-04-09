; Auto-generated. Do not edit!


(cl:in-package multi_amr_nectec-msg)


;//! \htmlinclude pos_msg.msg.html

(cl:defclass <pos_msg> (roslisp-msg-protocol:ros-message)
  ((point_robot
    :reader point_robot
    :initarg :point_robot
    :type (cl:vector geometry_msgs-msg:Point)
   :initform (cl:make-array 0 :element-type 'geometry_msgs-msg:Point :initial-element (cl:make-instance 'geometry_msgs-msg:Point))))
)

(cl:defclass pos_msg (<pos_msg>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <pos_msg>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'pos_msg)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name multi_amr_nectec-msg:<pos_msg> is deprecated: use multi_amr_nectec-msg:pos_msg instead.")))

(cl:ensure-generic-function 'point_robot-val :lambda-list '(m))
(cl:defmethod point_robot-val ((m <pos_msg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader multi_amr_nectec-msg:point_robot-val is deprecated.  Use multi_amr_nectec-msg:point_robot instead.")
  (point_robot m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <pos_msg>) ostream)
  "Serializes a message object of type '<pos_msg>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'point_robot))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'point_robot))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <pos_msg>) istream)
  "Deserializes a message object of type '<pos_msg>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'point_robot) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'point_robot)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'geometry_msgs-msg:Point))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<pos_msg>)))
  "Returns string type for a message object of type '<pos_msg>"
  "multi_amr_nectec/pos_msg")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'pos_msg)))
  "Returns string type for a message object of type 'pos_msg"
  "multi_amr_nectec/pos_msg")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<pos_msg>)))
  "Returns md5sum for a message object of type '<pos_msg>"
  "c9ace4191c815fda1591b79a1b91a4df")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'pos_msg)))
  "Returns md5sum for a message object of type 'pos_msg"
  "c9ace4191c815fda1591b79a1b91a4df")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<pos_msg>)))
  "Returns full string definition for message of type '<pos_msg>"
  (cl:format cl:nil "geometry_msgs/Point[] point_robot~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'pos_msg)))
  "Returns full string definition for message of type 'pos_msg"
  (cl:format cl:nil "geometry_msgs/Point[] point_robot~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <pos_msg>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'point_robot) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <pos_msg>))
  "Converts a ROS message object to a list"
  (cl:list 'pos_msg
    (cl:cons ':point_robot (point_robot msg))
))
