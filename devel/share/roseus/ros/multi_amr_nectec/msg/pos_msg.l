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
  :slots (_points2 _another_field2 ))

(defmethod multi_amr_nectec::pos_msg
  (:init
   (&key
    ((:points2 __points2) (let (r) (dotimes (i 0) (push (instance geometry_msgs::Point :init) r)) r))
    ((:another_field2 __another_field2) 0)
    )
   (send-super :init)
   (setq _points2 __points2)
   (setq _another_field2 (round __another_field2))
   self)
  (:points2
   (&rest __points2)
   (if (keywordp (car __points2))
       (send* _points2 __points2)
     (progn
       (if __points2 (setq _points2 (car __points2)))
       _points2)))
  (:another_field2
   (&optional __another_field2)
   (if __another_field2 (setq _another_field2 __another_field2)) _another_field2)
  (:serialization-length
   ()
   (+
    ;; geometry_msgs/Point[] _points2
    (apply #'+ (send-all _points2 :serialization-length)) 4
    ;; uint8 _another_field2
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; geometry_msgs/Point[] _points2
     (write-long (length _points2) s)
     (dolist (elem _points2)
       (send elem :serialize s)
       )
     ;; uint8 _another_field2
       (write-byte _another_field2 s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; geometry_msgs/Point[] _points2
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _points2 (let (r) (dotimes (i n) (push (instance geometry_msgs::Point :init) r)) r))
     (dolist (elem- _points2)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;; uint8 _another_field2
     (setq _another_field2 (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;;
   self)
  )

(setf (get multi_amr_nectec::pos_msg :md5sum-) "584ed9eab9daa1be705ab1b1de5c8229")
(setf (get multi_amr_nectec::pos_msg :datatype-) "multi_amr_nectec/pos_msg")
(setf (get multi_amr_nectec::pos_msg :definition-)
      "geometry_msgs/Point[] points2
uint8 another_field2
================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z

")



(provide :multi_amr_nectec/pos_msg "584ed9eab9daa1be705ab1b1de5c8229")


