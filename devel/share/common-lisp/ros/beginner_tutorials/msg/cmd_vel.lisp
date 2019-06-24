; Auto-generated. Do not edit!


(cl:in-package beginner_tutorials-msg)


;//! \htmlinclude cmd_vel.msg.html

(cl:defclass <cmd_vel> (roslisp-msg-protocol:ros-message)
  ((robot_cmd_vel
    :reader robot_cmd_vel
    :initarg :robot_cmd_vel
    :type (cl:vector geometry_msgs-msg:Twist)
   :initform (cl:make-array 0 :element-type 'geometry_msgs-msg:Twist :initial-element (cl:make-instance 'geometry_msgs-msg:Twist))))
)

(cl:defclass cmd_vel (<cmd_vel>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <cmd_vel>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'cmd_vel)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name beginner_tutorials-msg:<cmd_vel> is deprecated: use beginner_tutorials-msg:cmd_vel instead.")))

(cl:ensure-generic-function 'robot_cmd_vel-val :lambda-list '(m))
(cl:defmethod robot_cmd_vel-val ((m <cmd_vel>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader beginner_tutorials-msg:robot_cmd_vel-val is deprecated.  Use beginner_tutorials-msg:robot_cmd_vel instead.")
  (robot_cmd_vel m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <cmd_vel>) ostream)
  "Serializes a message object of type '<cmd_vel>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'robot_cmd_vel))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'robot_cmd_vel))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <cmd_vel>) istream)
  "Deserializes a message object of type '<cmd_vel>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'robot_cmd_vel) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'robot_cmd_vel)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'geometry_msgs-msg:Twist))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<cmd_vel>)))
  "Returns string type for a message object of type '<cmd_vel>"
  "beginner_tutorials/cmd_vel")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'cmd_vel)))
  "Returns string type for a message object of type 'cmd_vel"
  "beginner_tutorials/cmd_vel")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<cmd_vel>)))
  "Returns md5sum for a message object of type '<cmd_vel>"
  "156dca494411a2fd8068c53948502b64")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'cmd_vel)))
  "Returns md5sum for a message object of type 'cmd_vel"
  "156dca494411a2fd8068c53948502b64")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<cmd_vel>)))
  "Returns full string definition for message of type '<cmd_vel>"
  (cl:format cl:nil "geometry_msgs/Twist[] robot_cmd_vel~%~%================================================================================~%MSG: geometry_msgs/Twist~%# This expresses velocity in free space broken into its linear and angular parts.~%Vector3  linear~%Vector3  angular~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'cmd_vel)))
  "Returns full string definition for message of type 'cmd_vel"
  (cl:format cl:nil "geometry_msgs/Twist[] robot_cmd_vel~%~%================================================================================~%MSG: geometry_msgs/Twist~%# This expresses velocity in free space broken into its linear and angular parts.~%Vector3  linear~%Vector3  angular~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <cmd_vel>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'robot_cmd_vel) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <cmd_vel>))
  "Converts a ROS message object to a list"
  (cl:list 'cmd_vel
    (cl:cons ':robot_cmd_vel (robot_cmd_vel msg))
))
