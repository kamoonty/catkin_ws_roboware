;; Auto-generated. Do not edit!


(when (boundp 'multi_amr_nectec::pos_msg)
  (if (not (find-package "MULTI_AMR_NECTEC"))
    (make-package "MULTI_AMR_NECTEC"))
  (shadow 'pos_msg (find-package "MULTI_AMR_NECTEC")))
(unless (find-package "MULTI_AMR_NECTEC::POS_MSG")
  (make-package "MULTI_AMR_NECTEC::POS_MSG"))

(in-package "ROS")
;;//! \htmlinclude pos_msg.msg.html
(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))


(defclass multi_amr_nectec::pos_msg
  :super ros::object
  :slots (_point_robot ))

(defmethod multi_amr_nectec::pos_msg
  (:init
   (&key
    ((:point_robot __point_robot) (let (r) (dotimes (i 0) (push (instance geometry_msgs::Point :init) r)) r))
    )
   (send-super :init)
   (setq _point_robot __point_robot)
   self)
  (:point_robot
   (&rest __point_robot)
   (if (keywordp (car __point_robot))
       (send* _point_robot __point_robot)
     (progn
       (if __point_robot (setq _point_robot (car __point_robot)))
       _point_robot)))
  (:serialization-length
   ()
   (+
    ;; geometry_msgs/Point[] _point_robot
    (apply #'+ (send-all _point_robot :serialization-length)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; geometry_msgs/Point[] _point_robot
     (write-long (length _point_robot) s)
     (dolist (elem _point_robot)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; geometry_msgs/Point[] _point_robot
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _point_robot (let (r) (dotimes (i n) (push (instance geometry_msgs::Point :init) r)) r))
     (dolist (elem- _point_robot)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;;
   self)
  )

(setf (get multi_amr_nectec::pos_msg :md5sum-) "c9ace4191c815fda1591b79a1b91a4df")
(setf (get multi_amr_nectec::pos_msg :datatype-) "multi_amr_nectec/pos_msg")
(setf (get multi_amr_nectec::pos_msg :definition-)
      "geometry_msgs/Point[] point_robot

================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z

")



(provide :multi_amr_nectec/pos_msg "c9ace4191c815fda1591b79a1b91a4df")


