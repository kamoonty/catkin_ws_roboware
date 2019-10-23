;; Auto-generated. Do not edit!


(when (boundp 'beginner_tutorials::cmd_vel)
  (if (not (find-package "BEGINNER_TUTORIALS"))
    (make-package "BEGINNER_TUTORIALS"))
  (shadow 'cmd_vel (find-package "BEGINNER_TUTORIALS")))
(unless (find-package "BEGINNER_TUTORIALS::CMD_VEL")
  (make-package "BEGINNER_TUTORIALS::CMD_VEL"))

(in-package "ROS")
;;//! \htmlinclude cmd_vel.msg.html
(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))


(defclass beginner_tutorials::cmd_vel
  :super ros::object
  :slots (_robot_cmd_vel ))

(defmethod beginner_tutorials::cmd_vel
  (:init
   (&key
    ((:robot_cmd_vel __robot_cmd_vel) (let (r) (dotimes (i 0) (push (instance geometry_msgs::Twist :init) r)) r))
    )
   (send-super :init)
   (setq _robot_cmd_vel __robot_cmd_vel)
   self)
  (:robot_cmd_vel
   (&rest __robot_cmd_vel)
   (if (keywordp (car __robot_cmd_vel))
       (send* _robot_cmd_vel __robot_cmd_vel)
     (progn
       (if __robot_cmd_vel (setq _robot_cmd_vel (car __robot_cmd_vel)))
       _robot_cmd_vel)))
  (:serialization-length
   ()
   (+
    ;; geometry_msgs/Twist[] _robot_cmd_vel
    (apply #'+ (send-all _robot_cmd_vel :serialization-length)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; geometry_msgs/Twist[] _robot_cmd_vel
     (write-long (length _robot_cmd_vel) s)
     (dolist (elem _robot_cmd_vel)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; geometry_msgs/Twist[] _robot_cmd_vel
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _robot_cmd_vel (let (r) (dotimes (i n) (push (instance geometry_msgs::Twist :init) r)) r))
     (dolist (elem- _robot_cmd_vel)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;;
   self)
  )

(setf (get beginner_tutorials::cmd_vel :md5sum-) "156dca494411a2fd8068c53948502b64")
(setf (get beginner_tutorials::cmd_vel :datatype-) "beginner_tutorials/cmd_vel")
(setf (get beginner_tutorials::cmd_vel :definition-)
      "geometry_msgs/Twist[] robot_cmd_vel

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
")



(provide :beginner_tutorials/cmd_vel "156dca494411a2fd8068c53948502b64")


