
(cl:in-package :asdf)

(defsystem "multi_amr_nectec-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :geometry_msgs-msg
)
  :components ((:file "_package")
    (:file "pos_msg" :depends-on ("_package_pos_msg"))
    (:file "_package_pos_msg" :depends-on ("_package"))
  ))