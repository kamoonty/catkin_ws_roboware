;; Auto-generated. Do not edit!


(when (boundp 'beginner_tutorials::my_msg)
  (if (not (find-package "BEGINNER_TUTORIALS"))
    (make-package "BEGINNER_TUTORIALS"))
  (shadow 'my_msg (find-package "BEGINNER_TUTORIALS")))
(unless (find-package "BEGINNER_TUTORIALS::MY_MSG")
  (make-package "BEGINNER_TUTORIALS::MY_MSG"))

(in-package "ROS")
;;//! \htmlinclude my_msg.msg.html
(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))


(defclass beginner_tutorials::my_msg
  :super ros::object
  :slots (_points _another_field ))

(defmethod beginner_tutorials::my_msg
  (:init
   (&key
    ((:points __points) (let (r) (dotimes (i 0) (push (instance geometry_msgs::Point :init) r)) r))
    ((:another_field __another_field) 0)
    )
   (send-super :init)
   (setq _points __points)
   (setq _another_field (round __another_field))
   self)
  (:points
   (&rest __points)
   (if (keywordp (car __points))
       (send* _points __points)
     (progn
       (if __points (setq _points (car __points)))
       _points)))
  (:another_field
   (&optional __another_field)
   (if __another_field (setq _another_field __another_field)) _another_field)
  (:serialization-length
   ()
   (+
    ;; geometry_msgs/Point[] _points
    (apply #'+ (send-all _points :serialization-length)) 4
    ;; uint8 _another_field
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; geometry_msgs/Point[] _points
     (write-long (length _points) s)
     (dolist (elem _points)
       (send elem :serialize s)
       )
     ;; uint8 _another_field
       (write-byte _another_field s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; geometry_msgs/Point[] _points
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _points (let (r) (dotimes (i n) (push (instance geometry_msgs::Point :init) r)) r))
     (dolist (elem- _points)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;; uint8 _another_field
     (setq _another_field (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;;
   self)
  )

(setf (get beginner_tutorials::my_msg :md5sum-) "52b7cc5e44032cacb08a65980d276cc0")
(setf (get beginner_tutorials::my_msg :datatype-) "beginner_tutorials/my_msg")
(setf (get beginner_tutorials::my_msg :definition-)
      "geometry_msgs/Point[] points
uint8 another_field
================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z

")



(provide :beginner_tutorials/my_msg "52b7cc5e44032cacb08a65980d276cc0")


